"""
Competitive Programming Notebook Generator
==========================================
Escanea todos los archivos de codigo del repositorio, los agrupa por tema/subtema
(leido del comentario '// Tema: Tema / Subtema') y genera un PDF compacto estilo ICPC
con dos columnas en formato landscape, optimizado para impresion B/N.

Los numeros de linea se renderizan como texto invisible al copiar (ActualText trick).

Uso: python generate_notebook.py
     o doble-click en generate_notebook.bat
"""

import os
import re
import sys
import datetime
from pathlib import Path
from collections import OrderedDict, Counter

from reportlab.lib.pagesizes import letter, landscape
from reportlab.lib.units import inch, mm
from reportlab.lib.colors import HexColor, black, white, gray, Color
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont

# ─────────────────────────── CONFIGURACION ───────────────────────────

REPO_ROOT = Path(__file__).parent
EXTENSIONS = {".cpp", ".java", ".py", ".c", ".h", ".hpp"}
OUTPUT_FILE = REPO_ROOT / "notebook.pdf"

# Info del equipo
CONTEST_NAME = "XXXIX MARATON NACIONAL DE PROGRAMACION ACIS/REDIS 2026"
PARTICIPANTS = [
    "Juan David Reyes Cure",
    "Juan Felipe Rodriguez Barbosa",
    "Juan Esteban Rodriguez Castellanos",
]
COACH = "Stiven Correa"
UNIVERSITY = "Universidad de Ibague"

# Temas que son el mismo con otro nombre. Se unifican al escanear para que no
# salgan secciones repetidas en el indice (Graph/Graphs, String/Strings, ...).
TOPIC_ALIASES = {
    "Graphs": "Graph",
    "Search": "Graph",                  # State-Space BFS es busqueda en grafo
    "Strings": "String",
    "String Algorithms": "String",
    "Arrays": "Data Structures",
    "Trees": "Data Structures",
    "Bitmask DP": "Dynamic Programming",
    "Ad Hoc": "Implementation",
    "Ad-hoc": "Implementation",
    "Brute Force": "Implementation",
    "Recursion": "Implementation",
    "Simulation": "Implementation",     # en competitiva son lo mismo
}

# Orden de las secciones (basado en el indice del cpp.pdf de la UFPS)
SECTION_ORDER = [
    "Data Structures",
    "Dynamic Programming",
    "Graph",
    "Geometry",
    "Math",
    "Number Theory",
    "Combinatorics",
    "Game Theory",
    "String",
    "Greedy",
    "Binary Search",
    "Constructive Algorithms",
    "Implementation",
    "Formulario",
]

# Layout
PAGE_W, PAGE_H = landscape(letter)  # 792 x 612 pts = carta apaisada
# Margenes pensados para IMPRIMIR, no para leer en pantalla. Una impresora
# laser no imprime hasta el filo del papel: se come entre 4 y 6 mm de cada
# borde (el "area no imprimible"), y lo que caiga ahi sale cortado. 36 pt son
# 12.7 mm, asi que cualquier texto queda con 6 mm de colchon sobre el peor
# caso. SAFE_INSET es lo minimo que se respeta hasta para los fondos de
# color, que antes sangraban hasta el borde y salian recortados.
MARGIN_TOP = 36
MARGIN_BOTTOM = 36
MARGIN_LEFT = 36
MARGIN_RIGHT = 36
SAFE_INSET = 24          # 8.5 mm: ni un pixel de tinta mas afuera que esto
COL_GAP = 18

# ── Registrar fuentes TTF del sistema (soporte Unicode) ──
FONTS_DIR = Path(r"C:\Windows\Fonts")

def register_fonts():
    font_map = {
        "Consolas":       FONTS_DIR / "consola.ttf",
        "Consolas-Bold":  FONTS_DIR / "consolab.ttf",
        "SegoeUI":        FONTS_DIR / "segoeui.ttf",
        "SegoeUI-Bold":   FONTS_DIR / "segoeuib.ttf",
        "SegoeUI-Italic": FONTS_DIR / "segoeuii.ttf",
    }
    registered = {}
    for name, path in font_map.items():
        if path.exists():
            pdfmetrics.registerFont(TTFont(name, str(path)))
            registered[name] = True
        else:
            registered[name] = False
    return registered

FONTS_OK = register_fonts()

if FONTS_OK.get("Consolas"):
    CODE_FONT      = "Consolas"
    CODE_FONT_BOLD = "Consolas-Bold" if FONTS_OK.get("Consolas-Bold") else "Consolas"
else:
    CODE_FONT      = "Courier"
    CODE_FONT_BOLD = "Courier-Bold"

if FONTS_OK.get("SegoeUI"):
    TEXT_FONT        = "SegoeUI"
    TEXT_FONT_BOLD   = "SegoeUI-Bold"   if FONTS_OK.get("SegoeUI-Bold")   else "SegoeUI"
    TEXT_FONT_ITALIC = "SegoeUI-Italic" if FONTS_OK.get("SegoeUI-Italic") else "SegoeUI"
else:
    TEXT_FONT        = "Helvetica"
    TEXT_FONT_BOLD   = "Helvetica-Bold"
    TEXT_FONT_ITALIC = "Helvetica-Oblique"

CODE_SIZE    = 6.0
CODE_LEADING = 7.2

HEADER_FONT = TEXT_FONT_BOLD
HEADER_SIZE = 7.5

TITLE_FONT          = TEXT_FONT_BOLD
SECTION_TITLE_SIZE  = 10
SUBSECTION_TITLE_SIZE = 7.5

DESC_FONT = TEXT_FONT_ITALIC
DESC_SIZE = 6.2

TOC_FONT      = TEXT_FONT
TOC_SIZE      = 7.5
TOC_FONT_BOLD = TEXT_FONT_BOLD

# Colores B/N optimizados
BG_DARK       = HexColor("#222222")   # casi negro para headers
BG_MID        = HexColor("#444444")   # gris oscuro para secciones
TEXT_WHITE     = white
TEXT_BLACK     = black
TEXT_GRAY      = HexColor("#666666")
TEXT_LIGHT     = HexColor("#999999")
LINE_NUM_COLOR = HexColor("#aaaaaa")
CODE_BG_ALT    = HexColor("#f0f0f0")  # filas alternadas
SEPARATOR_COLOR = HexColor("#cccccc")


# ─────────────────────── ESCANEO DE ARCHIVOS ─────────────────────────

def scan_files(root: Path):
    """Busca archivos de codigo y extrae tema, subtema, descripcion y contenido."""
    files = []
    for ext in EXTENSIONS:
        for filepath in root.rglob(f"*{ext}"):
            if filepath.name in ("generate_notebook.py",):
                continue
            if any(part.startswith(".") for part in filepath.parts):
                continue
            files.append(filepath)

    entries = []
    for fp in sorted(files):
        content = fp.read_text(encoding="utf-8", errors="replace")
        lines = content.split("\n")

        topic = "Uncategorized"
        subtopic = ""
        description = ""
        code_lines = []
        meta_ended = False

        if fp.suffix in (".py",):
            comment_prefix = "#"
        else:
            comment_prefix = "//"

        for line in lines:
            stripped = line.strip()
            m_topic = re.match(rf"^{re.escape(comment_prefix)}\s*Tema:\s*(.+)", stripped)

            if m_topic and not meta_ended:
                raw = m_topic.group(1).strip()
                if "/" in raw:
                    parts = raw.split("/", 1)
                    topic = parts[0].strip()
                    subtopic = parts[1].strip()
                else:
                    topic = raw
                    subtopic = raw
            elif stripped == f"{comment_prefix} <3" and not meta_ended:
                continue
            elif stripped.startswith(comment_prefix) and not meta_ended:
                desc_match = re.match(rf"^{re.escape(comment_prefix)}\s*(.*)", stripped)
                if desc_match:
                    desc_text = desc_match.group(1).strip()
                    if desc_text and desc_text != "<3" and not desc_text.startswith("Tema:"):
                        description += (" " if description else "") + desc_text
            else:
                meta_ended = True
                code_lines.append(line)

        while code_lines and not code_lines[0].strip():
            code_lines.pop(0)
        while code_lines and not code_lines[-1].strip():
            code_lines.pop()

        if not subtopic:
            subtopic = fp.stem

        # Los de CSES no entran a las secciones por tema: van a un apartado
        # aparte al final, subdividido por la carpeta de CSES a la que
        # pertenecen ("Introductory Problems", "Graph Algorithms", ...). El
        # subtema sigue siendo la tecnica, que es lo que se busca.
        partes = fp.relative_to(root).parts
        if "CSES" in partes:
            i = partes.index("CSES")
            carpeta = partes[i + 1] if i + 1 < len(partes) - 1 else "Sin Carpeta"
            topic = "CSES: " + carpeta

        entries.append({
            "name": fp.stem,
            "topic": TOPIC_ALIASES.get(topic, topic),
            "subtopic": subtopic,
            "description": description,
            "code": "\n".join(code_lines),
            "path": str(fp.relative_to(root)),
            "extension": fp.suffix,
        })

    return entries


def pretty_name(stem):
    """Nombre legible del problema: '0001_two_sum' o 'L - Less_coint_tosses' -> 'Two Sum'."""
    s = re.sub(r"^\d+[_\s-]+", "", stem)      # prefijo numerico de LeetCode
    s = re.sub(r"^[A-Za-z]\s*-\s*", "", s)    # prefijo de letra de problema ("L - ")
    s = s.replace("_", " ").replace("-", " ")
    s = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", " ", s)   # camelCase -> "camel Case"
    s = re.sub(r"\s+", " ", s).strip()
    # Solo se capitaliza lo que venia todo en minuscula, para no destrozar
    # siglas ya escritas bien (LLMs, AROD, SQL).
    return " ".join(w.capitalize() if w.islower() else w for w in s.split(" ")) or stem


def source_tag(path):
    """De donde viene el problema: 'Day 4', 'Codeforces', 'RPC', ... o '' si no aplica."""
    parts = str(path).replace("\\", "/").split("/")
    for p in parts:
        if p.lower().startswith("day "):
            return p.split(" - ")[0].strip()   # "Day 11 - CCPL" -> "Day 11"
    # ICPC se guarda por ano (C++/ICPC/2024/...), asi que la etiqueta lleva el ano
    for i, p in enumerate(parts):
        if p == "ICPC":
            if i + 1 < len(parts) - 1 and parts[i + 1].isdigit():
                return "ICPC " + parts[i + 1]
            return "ICPC"
    for p in parts:
        if p in ("Codeforces", "LeetCode", "RPC", "CCPL", "CSES",
                  "Notebook", "Formulario"):
            return p
    return ""


def group_by_topic(entries):
    """Agrupa entradas por tema en el orden definido."""
    groups = OrderedDict()
    for section in SECTION_ORDER:
        group = [e for e in entries if e["topic"] == section]
        if group:
            groups[section] = sorted(group, key=lambda e: e["subtopic"].lower())

    known = set(SECTION_ORDER)
    extra = sorted(set(e["topic"] for e in entries if e["topic"] not in known))
    # CSES de ultimo, siempre, sin importar el alfabeto.
    es_cses = lambda t: t.startswith("CSES: ")
    extra = [t for t in extra if not es_cses(t)] + [t for t in extra if es_cses(t)]
    for topic in extra:
        group = [e for e in entries if e["topic"] == topic]
        if group:
            groups[topic] = sorted(group, key=lambda e: e["subtopic"].lower())

    # Etiqueta del indice: SIEMPRE lleva el nombre del problema, porque uno se
    # acuerda del titulo ("Mail Delivery") mucho mas que de la tecnica
    # ("Circuito Euleriano"). La tecnica va primero porque la lista esta
    # ordenada por subtema; para buscar por titulo esta el indice alfabetico.
    for items in groups.values():
        for item in items:
            nombre = pretty_name(item["name"])
            item["problem"] = nombre
            item["source"] = source_tag(item["path"])
            plano = lambda x: re.sub(r"[^a-z0-9]", "", x.lower())
            if plano(nombre) in plano(item["subtopic"]):
                item["label"] = item["subtopic"]
            elif item["topic"].startswith("CSES: "):
                # En CSES manda el nombre del problema: uno los busca por
                # titulo, no por tecnica. La tecnica va detras como apoyo.
                item["label"] = f"{nombre} - {item['subtopic']}"
            else:
                item["label"] = f"{item['subtopic']} - {nombre}"

        # Los de CSES se ordenan por nombre de problema (el resto va por
        # subtema). Se hace aqui y no arriba porque "problem" recien se calculo.
        if items and items[0]["topic"].startswith("CSES: "):
            items.sort(key=lambda e: e["problem"].lower())

        # Si dos quedan con la misma etiqueta, desempatar con el lenguaje.
        dup = Counter(i["label"] for i in items)
        for item in items:
            if dup[item["label"]] > 1:
                item["label"] += f" ({item['extension'].lstrip('.')})"

    return groups


# ───────────────────────── GENERADOR DE PDF ──────────────────────────

class NotebookPDF:
    def __init__(self, output_path, groups, page_of=None):
        self.output_path = str(output_path)
        self.groups = groups
        # bookmark_key -> numero de pagina IMPRESO donde arranca ese subtitulo.
        # Viene de una primera pasada: la pagina no se sabe hasta que el PDF
        # entero esta armado, asi que se genera dos veces (ver main()). El
        # ancho reservado para el numero es fijo, por eso las dos pasadas dan
        # exactamente el mismo layout y la segunda no desplaza nada.
        self.page_of = page_of or {}
        self.c = canvas.Canvas(self.output_path, pagesize=landscape(letter))
        self.c.setTitle("Notebook - " + UNIVERSITY)
        self.c.setAuthor(UNIVERSITY)
        self.page_num = 0

        self.col_width = (PAGE_W - MARGIN_LEFT - MARGIN_RIGHT - COL_GAP) / 2
        # debajo de la barra del encabezado (SAFE_INSET + alto de barra + aire)
        self.content_top = PAGE_H - SAFE_INSET - 14 - 8
        self.content_bottom = MARGIN_BOTTOM

        self.col = 0
        self.y = self.content_top

        # Bookmarks para los links del TOC: key -> (indice 0-based de pagina, y).
        # Se usa page_num y no un contador aparte porque page_num ES el indice
        # de la pagina que se esta dibujando (cuenta los showPage ya hechos).
        self.bookmarks = {}

    def col_x(self):
        if self.col == 0:
            return MARGIN_LEFT
        return MARGIN_LEFT + self.col_width + COL_GAP

    def next_column(self):
        if self.col == 0:
            self.col = 1
            self.y = self.content_top
        else:
            self._new_page()

    def _new_page(self):
        self._draw_header()
        self.c.showPage()
        self.page_num += 1
        self.col = 0
        self.y = self.content_top

    def _draw_header(self):
        # Barra del encabezado. Antes empezaba en PAGE_H - 18 y se extendia de
        # borde a borde, asi que al imprimir se cortaba y el numero de pagina
        # quedaba a 4.8 mm del filo, justo en la zona que la impresora no
        # alcanza. Ahora la barra vive dentro del area segura.
        barra_alto = 14
        barra_top = PAGE_H - SAFE_INSET
        self.c.setFillColor(BG_DARK)
        self.c.rect(MARGIN_LEFT, barra_top - barra_alto,
                    PAGE_W - MARGIN_LEFT - MARGIN_RIGHT, barra_alto,
                    fill=True, stroke=False)
        self.c.setFillColor(TEXT_WHITE)
        self.c.setFont(HEADER_FONT, HEADER_SIZE)
        base = barra_top - barra_alto + 4
        self.c.drawString(MARGIN_LEFT + 5, base, f"{UNIVERSITY}  -  NOTEBOOK")
        self.c.drawRightString(PAGE_W - MARGIN_RIGHT - 5, base,
                               str(self.page_num + 1))

        # Linea inferior
        self.c.setStrokeColor(BG_MID)
        self.c.setLineWidth(0.4)
        self.c.line(MARGIN_LEFT, MARGIN_BOTTOM - 4,
                    PAGE_W - MARGIN_RIGHT, MARGIN_BOTTOM - 4)

    def ensure_space(self, needed):
        if self.y - needed < self.content_bottom:
            self.next_column()

    def draw_section_title(self, number, title):
        h = 15
        self.ensure_space(h + 6)
        x = self.col_x()

        self.c.setFillColor(BG_MID)
        self.c.roundRect(x, self.y - h, self.col_width, h, 2, fill=True, stroke=False)

        self.c.setFillColor(TEXT_WHITE)
        self.c.setFont(TITLE_FONT, SECTION_TITLE_SIZE)
        self.c.drawString(x + 5, self.y - h + 4, f"{number} - {title}")
        self.y -= h + 5

    def wrap_desc(self, desc):
        """Parte la descripcion midiendo el ancho REAL de cada linea.

        Antes se estimaba con un factor fijo de caracteres por linea y la
        mitad de las descripciones se salian de la columna y se cortaban.
        """
        disponible = self.col_width - 4
        lineas = []
        linea = ""
        for palabra in desc.split():
            prueba = (linea + " " + palabra).strip()
            if linea and self.c.stringWidth(prueba, DESC_FONT, DESC_SIZE) > disponible:
                lineas.append(linea)
                linea = palabra
            else:
                linea = prueba
        if linea:
            lineas.append(linea)
        return lineas

    def draw_subsection_title(self, number, subtopic, desc, path, bookmark_key):
        needed = 12
        if desc:
            desc_lines = len(self.wrap_desc(desc))
            needed += desc_lines * (DESC_SIZE + 2) + 2

        self.ensure_space(needed + CODE_LEADING * 3)
        x = self.col_x()

        # Registrar posicion para el link del TOC
        self.bookmarks[bookmark_key] = (self.page_num, self.y)

        # Bookmark PDF nativo
        self.c.bookmarkHorizontal(bookmark_key, x, self.y + 2)

        # Separador
        self.c.setStrokeColor(SEPARATOR_COLOR)
        self.c.setLineWidth(0.3)
        self.c.line(x, self.y, x + self.col_width, self.y)
        self.y -= 3

        # Subtema como titulo
        self.c.setFillColor(TEXT_BLACK)
        self.c.setFont(TITLE_FONT, SUBSECTION_TITLE_SIZE)
        self.c.drawString(x + 2, self.y - 8, f"{number}  {subtopic}")
        self.y -= 11

        # Path en gris
        self.c.setFont(TEXT_FONT, 4.5)
        self.c.setFillColor(TEXT_LIGHT)
        self.c.drawString(x + 2, self.y - 1, path)
        self.y -= 7

        # Descripcion en italica
        if desc:
            self.c.setFont(DESC_FONT, DESC_SIZE)
            self.c.setFillColor(TEXT_GRAY)
            for linea in self.wrap_desc(desc):
                self.c.drawString(x + 2, self.y - 1, linea)
                self.y -= DESC_SIZE + 2
            self.y -= 1

    def _draw_digit_paths(self, x, y, digit_str, size):
        """Dibuja digitos como mini-paths vectoriales (no texto), asi no se copian."""
        # Segmentos tipo display de 7 segmentos para cada digito
        # Cada digito ocupa un box de (size*0.6) ancho x size alto
        w = size * 0.55
        h = size * 0.9
        t = size * 0.1  # grosor de trazo
        gap = size * 0.08

        # Coordenadas de los 7 segmentos: (x1,y1,x2,y2) relativo al box
        segs = {
            #       top          top-r        bot-r        bottom       bot-l        top-l        middle
            '0': [True,  True,  True,  True,  True,  True,  False],
            '1': [False, True,  True,  False, False, False, False],
            '2': [True,  True,  False, True,  True,  False, True],
            '3': [True,  True,  True,  True,  False, False, True],
            '4': [False, True,  True,  False, False, True,  True],
            '5': [True,  False, True,  True,  False, True,  True],
            '6': [True,  False, True,  True,  True,  True,  True],
            '7': [True,  True,  True,  False, False, False, False],
            '8': [True,  True,  True,  True,  True,  True,  True],
            '9': [True,  True,  True,  True,  False, True,  True],
        }

        self.c.setFillColor(LINE_NUM_COLOR)
        self.c.setStrokeColor(LINE_NUM_COLOR)
        self.c.setLineWidth(t)

        total_width = len(digit_str) * (w + gap) - gap
        start_x = x - total_width  # alineado a la derecha

        for ch in digit_str:
            if ch not in segs:
                start_x += w + gap
                continue
            s = segs[ch]
            bx = start_x
            by = y

            hh = h / 2  # mitad de altura
            # top (horizontal)
            if s[0]:
                self.c.line(bx + t, by + h, bx + w - t, by + h)
            # top-right (vertical)
            if s[1]:
                self.c.line(bx + w, by + hh + t/2, bx + w, by + h - t)
            # bottom-right (vertical)
            if s[2]:
                self.c.line(bx + w, by + t, bx + w, by + hh - t/2)
            # bottom (horizontal)
            if s[3]:
                self.c.line(bx + t, by, bx + w - t, by)
            # bottom-left (vertical)
            if s[4]:
                self.c.line(bx, by + t, bx, by + hh - t/2)
            # top-left (vertical)
            if s[5]:
                self.c.line(bx, by + hh + t/2, bx, by + h - t)
            # middle (horizontal)
            if s[6]:
                self.c.line(bx + t, by + hh, bx + w - t, by + hh)

            start_x += w + gap

    @staticmethod
    def es_prosa(linea):
        """Distingue una explicacion en palabras de una formula o tabla.

        Las formulas van en monoespaciado (si no, las tablas de valores pierden
        la alineacion); las explicaciones van en proporcional para que se note
        de un vistazo que son texto y no matematica.
        """
        t = linea.strip()
        if not t:
            return False
        if re.search(r"\s{3,}", t):          # columnas alineadas = tabla
            return False
        if re.search(r"[=^*/|<>]", t):       # simbolos matematicos
            return False
        if re.search(r"\b[A-Za-z]\(", t):    # llamada tipo f(x) o C(n,k)
            return False
        # Ante la duda se prefiere tratarlo como codigo: una formula en letra
        # proporcional solo se ve distinta, pero codigo en italica se ve roto.
        if re.search(r"[{};&]|->|::|\+\+|--", t):
            return False
        if re.match(r"(int|ll|long|double|bool|void|auto|return|for|while|if|"
                    r"else|vector|pair|switch|case|string|const|struct)\b", t):
            return False
        return len(re.findall(r"[A-Za-z]{3,}", t)) >= 4

    def wrap_ancho(self, texto, fuente, tam, ancho):
        """Parte un texto midiendo el ancho real (nunca contando caracteres)."""
        salida, linea = [], ""
        for palabra in texto.split():
            prueba = (linea + " " + palabra).strip()
            if linea and self.c.stringWidth(prueba, fuente, tam) > ancho:
                salida.append(linea)
                linea = palabra
            else:
                linea = prueba
        if linea:
            salida.append(linea)
        return salida

    def draw_formulario(self, texto):
        """Renderiza una ficha del Formulario como hoja de formulas, no como codigo.

        Las fichas del Formulario son comentarios de principio a fin. Pasarlas por
        draw_code las llenaba de '//', numeros de linea y bandas grises alternadas,
        que es ruido puro en una hoja de consulta. Aqui se quita el prefijo, los
        titulos de bloque se dibujan como SUBTITULOS de verdad (negrita, con una
        regla fina debajo) y el resto se deja en monoespaciado para que las tablas
        de valores sigan cuadrando columna con columna.
        """
        interlinea = CODE_LEADING

        crudas = []
        for linea in texto.split("\n"):
            st = linea.strip()
            if st.startswith("//"):
                st = st[2:]
            elif st.startswith("#"):
                st = st[1:]
            if st.startswith(" "):
                st = st[1:]
            crudas.append(st.rstrip())

        # La banda "=== TITULO ===" repite el subtitulo de la seccion: sobra.
        while crudas and (not crudas[0] or re.match(r"^=+.*=+$", crudas[0])):
            crudas.pop(0)

        char_w = self.c.stringWidth("M", CODE_FONT, CODE_SIZE)
        max_chars = int((self.col_width - 8) / char_w)

        primera = True
        for linea in crudas:
            if not linea.strip():
                self.y -= interlinea * 0.45
                continue

            es_subtitulo = not linea.startswith(" ")

            if es_subtitulo:
                # Un subtitulo solo no debe quedar al final de la columna.
                self.ensure_space(interlinea * 3.2)
                if not primera:
                    self.y -= interlinea * 0.5
                # OJO: ensure_space puede cambiar de columna o de pagina, asi que
                # la x se recalcula SIEMPRE despues de llamarla, nunca antes.
                x = self.col_x()
                self.c.setFont(TEXT_FONT_BOLD, 7.2)
                self.c.setFillColor(TEXT_BLACK)
                self.c.drawString(x + 1, self.y - 7, linea.strip())
                self.y -= 9
                self.c.setStrokeColor(SEPARATOR_COLOR)
                self.c.setLineWidth(0.3)
                self.c.line(x + 1, self.y + 1.5, x + self.col_width - 4, self.y + 1.5)
                self.y -= 2.5
            elif self.es_prosa(linea):
                # Explicacion: tipografia proporcional en gris, se distingue de la formula.
                sangria = len(linea) - len(linea.lstrip())
                for trozo in self.wrap_ancho(linea.strip(), TEXT_FONT_ITALIC, DESC_SIZE,
                                             self.col_width - 10 - sangria * 1.5):
                    self.ensure_space(interlinea + 1)
                    x = self.col_x()
                    self.c.setFont(TEXT_FONT_ITALIC, DESC_SIZE)
                    self.c.setFillColor(TEXT_GRAY)
                    self.c.drawString(x + 6 + sangria * 1.5, self.y - interlinea + 3.5, trozo)
                    self.y -= interlinea
            else:
                # Formula o tabla: monoespaciado, que es lo que mantiene las columnas.
                trozo = linea
                while True:
                    self.ensure_space(interlinea + 1)
                    x = self.col_x()
                    self.c.setFont(CODE_FONT, CODE_SIZE)
                    self.c.setFillColor(TEXT_BLACK)
                    self.c.drawString(x + 6, self.y - interlinea + 3.5, trozo[:max_chars])
                    self.y -= interlinea
                    if len(trozo) <= max_chars:
                        break
                    trozo = "      " + trozo[max_chars:]
            primera = False

        self.y -= 4

    def draw_code(self, code):
        lines = code.split("\n")
        line_num_width = 20

        max_code_width = self.col_width - line_num_width - 4
        char_width = self.c.stringWidth("M", CODE_FONT, CODE_SIZE)
        max_chars = int(max_code_width / char_width)

        processed_lines = []
        for i, line in enumerate(lines):
            expanded = line.replace("\t", "    ")
            while len(expanded) > max_chars:
                processed_lines.append((i + 1, expanded[:max_chars], False))
                expanded = "    " + expanded[max_chars:]
            processed_lines.append((i + 1, expanded, True))

        for line_num, text, is_first in processed_lines:
            self.ensure_space(CODE_LEADING + 1)

            curr_x = self.col_x()
            code_curr_x = curr_x + line_num_width

            # Fondo alternado
            if line_num % 2 == 0 and is_first:
                self.c.setFillColor(CODE_BG_ALT)
                self.c.rect(curr_x, self.y - CODE_LEADING + 2,
                           self.col_width, CODE_LEADING, fill=True, stroke=False)

            # Numero de linea como paths vectoriales (no se copian)
            if is_first:
                self._draw_digit_paths(
                    curr_x + line_num_width - 5,
                    self.y - CODE_LEADING + 3.5,
                    str(line_num),
                    CODE_SIZE - 1.2
                )

            # Codigo (texto real, se copia normalmente)
            self.c.setFont(CODE_FONT, CODE_SIZE)
            self.c.setFillColor(TEXT_BLACK)
            self.c.drawString(code_curr_x + 1, self.y - CODE_LEADING + 4, text)

            self.y -= CODE_LEADING

        self.y -= 4

    def draw_asignacion(self):
        """Hoja de reparto, la primera del cuaderno.

        Es para llenar A MANO durante el contest: quien leyo cada problema, de
        que parece ser y que tan duro se ve. Sirve para no leer dos veces lo
        mismo y para que el que sabe del tema lo agarre. Por eso las columnas
        de los tres son angostas (una marca basta) y Tematica es la mas ancha.
        """
        # Filas: un problema por letra, A hasta N (14, lo tipico de la nacional)
        letras = [chr(ord("A") + i) for i in range(14)]
        columnas = [
            ("Problema",   56, "centro"),
            ("Juan",       52, "centro"),
            ("Felipe",     52, "centro"),
            ("Reyes",      52, "centro"),
            ("Tematica",  328, "izq"),
            ("Dificultad", 180, "izq"),
        ]
        ancho_total = sum(c[1] for c in columnas)

        y = PAGE_H - MARGIN_TOP - 8

        # Titulo
        self.c.setFillColor(TEXT_BLACK)
        self.c.setFont(TEXT_FONT_BOLD, 15)
        self.c.drawString(MARGIN_LEFT, y, "REPARTO DE PROBLEMAS")
        self.c.setFont(TEXT_FONT, 8)
        self.c.setFillColor(TEXT_GRAY)
        self.c.drawRightString(MARGIN_LEFT + ancho_total, y + 2,
                               UNIVERSITY + "   -   " + CONTEST_NAME)
        y -= 12
        self.c.setFont(TEXT_FONT_ITALIC, 7.5)
        self.c.setFillColor(TEXT_LIGHT)
        self.c.drawString(MARGIN_LEFT, y,
                          "Marca quien ya lo leyo. En Tematica anota de que se trata; "
                          "en Dificultad, que tan duro se ve y si vale la pena ahora.")
        y -= 14

        # Alto de fila: se reparte todo lo que queda hasta el margen de abajo
        filas = len(letras) + 1                      # + encabezado
        alto_fila = (y - MARGIN_BOTTOM) / filas
        tabla_top = y

        # ---- encabezado ----
        self.c.setFillColor(BG_DARK)
        self.c.rect(MARGIN_LEFT, tabla_top - alto_fila, ancho_total, alto_fila,
                    fill=True, stroke=False)
        self.c.setFillColor(TEXT_WHITE)
        self.c.setFont(TEXT_FONT_BOLD, 9)
        x = MARGIN_LEFT
        base_cab = tabla_top - alto_fila + (alto_fila - 9) / 2 + 1.5
        for nombre, ancho, alineado in columnas:
            if alineado == "centro":
                self.c.drawCentredString(x + ancho / 2, base_cab, nombre)
            else:
                self.c.drawString(x + 6, base_cab, nombre)
            x += ancho

        # ---- filas ----
        self.c.setFont(TEXT_FONT_BOLD, 12)
        for i, letra in enumerate(letras):
            fila_top = tabla_top - alto_fila * (i + 1)
            fila_bot = fila_top - alto_fila

            # Franjas suaves alternadas: con 14 filas y columnas anchas, seguir
            # la linea con el ojo es mas facil asi que con puras rayas.
            if i % 2 == 1:
                self.c.setFillColor(HexColor("#F4F4F4"))
                self.c.rect(MARGIN_LEFT, fila_bot, ancho_total, alto_fila,
                            fill=True, stroke=False)

            # La letra del problema, que es lo que se busca de un vistazo
            self.c.setFillColor(TEXT_BLACK)
            self.c.setFont(TEXT_FONT_BOLD, 12)
            self.c.drawCentredString(MARGIN_LEFT + columnas[0][1] / 2,
                                     fila_bot + (alto_fila - 12) / 2 + 2, letra)

            # Casilla para marcar en cada una de las tres columnas de persona
            x = MARGIN_LEFT + columnas[0][1]
            lado = min(11.0, alto_fila - 10)
            for _, ancho, _a in columnas[1:4]:
                self.c.setStrokeColor(HexColor("#9A9A9A"))
                self.c.setLineWidth(0.6)
                self.c.rect(x + (ancho - lado) / 2,
                            fila_bot + (alto_fila - lado) / 2,
                            lado, lado, fill=False, stroke=True)
                x += ancho

            # Renglon tenue para escribir dentro de Tematica y Dificultad
            for _, ancho, _a in columnas[4:]:
                self.c.setStrokeColor(HexColor("#D0D0D0"))
                self.c.setLineWidth(0.4)
                self.c.line(x + 6, fila_bot + 5, x + ancho - 6, fila_bot + 5)
                x += ancho

        # ---- rejilla ----
        tabla_bot = tabla_top - alto_fila * filas
        self.c.setStrokeColor(HexColor("#8A8A8A"))
        self.c.setLineWidth(0.5)
        for i in range(filas + 1):
            yy = tabla_top - alto_fila * i
            self.c.line(MARGIN_LEFT, yy, MARGIN_LEFT + ancho_total, yy)
        x = MARGIN_LEFT
        for _, ancho, _a in columnas:
            self.c.line(x, tabla_top, x, tabla_bot)
            x += ancho
        self.c.line(x, tabla_top, x, tabla_bot)

        self.c.showPage()
        self.page_num += 1

    def draw_cover(self, groups):
        """Portada con info del equipo y TOC con links."""
        # ---- HEADER OSCURO ----
        cab_top = PAGE_H - SAFE_INSET
        cab_alto = 62
        self.c.setFillColor(BG_DARK)
        self.c.rect(MARGIN_LEFT, cab_top - cab_alto,
                    PAGE_W - MARGIN_LEFT - MARGIN_RIGHT, cab_alto,
                    fill=True, stroke=False)

        # Nombre del concurso
        self.c.setFillColor(TEXT_WHITE)
        self.c.setFont(TEXT_FONT_BOLD, 13)
        self.c.drawCentredString(PAGE_W / 2, cab_top - 20, CONTEST_NAME)

        # Linea decorativa
        dash_text = " - " * 22
        self.c.setFont(TEXT_FONT, 8)
        self.c.setFillColor(HexColor("#888888"))
        self.c.drawCentredString(PAGE_W / 2, cab_top - 35,
                                 dash_text + "NOTEBOOK" + dash_text)

        # Universidad
        self.c.setFont(TEXT_FONT_BOLD, 11)
        self.c.setFillColor(TEXT_WHITE)
        self.c.drawCentredString(PAGE_W / 2, cab_top - 52, UNIVERSITY)

        # ---- INFO DEL EQUIPO ----
        info_y = cab_top - cab_alto - 20

        # Participantes
        self.c.setFont(TEXT_FONT_BOLD, 9)
        self.c.setFillColor(TEXT_BLACK)
        self.c.drawString(MARGIN_LEFT + 40, info_y, "Participantes:")
        info_y -= 13
        self.c.setFont(TEXT_FONT, 8.5)
        self.c.setFillColor(TEXT_GRAY)
        for name in PARTICIPANTS:
            self.c.drawString(MARGIN_LEFT + 55, info_y, name)
            info_y -= 12

        # Entrenador
        info_y -= 4
        self.c.setFont(TEXT_FONT_BOLD, 9)
        self.c.setFillColor(TEXT_BLACK)
        self.c.drawString(MARGIN_LEFT + 40, info_y, "Entrenador:")
        info_y -= 13
        self.c.setFont(TEXT_FONT, 8.5)
        self.c.setFillColor(TEXT_GRAY)
        self.c.drawString(MARGIN_LEFT + 55, info_y, COACH)

        # Fecha (lado derecho del bloque de info)
        self.c.setFont(TEXT_FONT, 8)
        self.c.setFillColor(TEXT_LIGHT)
        self.c.drawRightString(PAGE_W - MARGIN_RIGHT - 40, cab_top - cab_alto - 20,
                               datetime.date.today().strftime("%B %d, %Y"))

        # ---- TABLA DE CONTENIDOS ----
        # Puede ocupar mas de una pagina fisica si hay muchas entradas: cuando
        # ambas columnas de una pagina se llenan, se agrega una pagina nueva
        # en vez de sobreescribir el contenido ya dibujado.
        toc_y = cab_top - cab_alto - 115
        self.c.setFont(TEXT_FONT_BOLD, 12)
        self.c.setFillColor(TEXT_BLACK)
        self.c.drawString(MARGIN_LEFT + 40, toc_y, "Contents")
        toc_y -= 18

        # Dividir en dos columnas
        toc_col_width = (PAGE_W - MARGIN_LEFT * 2 - 80) / 2
        toc_x_left = MARGIN_LEFT + 50
        toc_x_right = toc_x_left + toc_col_width + 20
        toc_x = toc_x_left
        toc_y_start = toc_y
        toc_top_cont = self.content_top - 12   # inicio de columna al continuar

        # toc_page_idx: indice (0-based) de la pagina fisica del TOC en la que
        # estamos dibujando en este momento (0 = esta misma portada).
        toc_page_idx = 0

        # Guardar posiciones de los links para aplicar despues: (pagina, rect, bookmark_key)
        self.toc_links = []

        def new_toc_page():
            nonlocal toc_x, toc_y, toc_page_idx
            self.c.showPage()
            self.page_num += 1
            toc_page_idx += 1
            self.c.setFont(TEXT_FONT_BOLD, 11)
            self.c.setFillColor(TEXT_BLACK)
            self.c.drawString(MARGIN_LEFT + 40, toc_top_cont, "Contents (cont.)")
            toc_x = toc_x_left
            toc_y = toc_top_cont - 18

        def advance_column():
            nonlocal toc_x, toc_y
            if toc_x == toc_x_left:
                toc_x = toc_x_right
                toc_y = toc_y_start if toc_page_idx == 0 else (toc_top_cont - 18)
            else:
                new_toc_page()

        section_num = 0

        for section_name, items in groups.items():
            section_num += 1

            # Espacio para el titulo de seccion + al menos una entrada
            if toc_y < MARGIN_BOTTOM + 30:
                advance_column()

            # Titulo de seccion
            self.c.setFont(TOC_FONT_BOLD, TOC_SIZE)
            self.c.setFillColor(BG_MID)
            self.c.drawString(toc_x, toc_y, f"{section_num}  {section_name}")
            toc_y -= 12

            for idx, item in enumerate(items):
                if toc_y < MARGIN_BOTTOM + 30:
                    advance_column()

                sub_num = f"{section_num}.{idx + 1}"
                label = f"    {sub_num}  {item['label']}"

                bookmark_key = f"sec_{section_num}_{idx}"
                self.c.setFont(TOC_FONT, TOC_SIZE - 1)
                self.c.setFillColor(TEXT_GRAY)
                self.c.drawString(toc_x + 8, toc_y, label)

                # Numero de pagina donde arranca este subtitulo. El ancho
                # reservado es fijo (ANCHO_NUM) para que la pasada sin numeros
                # y la pasada con numeros produzcan el mismo layout.
                ANCHO_NUM = 18
                num = self.page_of.get(bookmark_key)
                if num:
                    self.c.setFont(TOC_FONT_BOLD, TOC_SIZE - 1)
                    self.c.setFillColor(TEXT_BLACK)
                    self.c.drawRightString(toc_x + toc_col_width - 10, toc_y, str(num))
                    self.c.setFont(TOC_FONT, TOC_SIZE - 1)
                    self.c.setFillColor(TEXT_GRAY)

                # Dots
                dots_x = toc_x + toc_col_width - 10 - ANCHO_NUM
                text_width = self.c.stringWidth(label, TOC_FONT, TOC_SIZE - 1)
                dot_start = toc_x + 8 + text_width + 4
                if dot_start < dots_x - 10:
                    num_dots = int((dots_x - dot_start) / 3)
                    self.c.setFillColor(SEPARATOR_COLOR)
                    self.c.drawString(dot_start, toc_y, "." * num_dots)

                # Guardar info del link para aplicar despues de generar bookmarks
                link_rect = (toc_x + 8, toc_y - 2,
                             toc_x + toc_col_width, toc_y + TOC_SIZE)
                self.toc_links.append((toc_page_idx, link_rect, bookmark_key))

                toc_y -= 11

            toc_y -= 4

        # Stats (en la ultima pagina del TOC)
        total_files = sum(len(items) for items in groups.values())
        total_lines = sum(
            len(item["code"].split("\n"))
            for items in groups.values()
            for item in items
        )
        stats_y = MARGIN_BOTTOM + 15
        self.c.setFont(TEXT_FONT, 7)
        self.c.setFillColor(TEXT_LIGHT)
        self.c.drawCentredString(PAGE_W / 2, stats_y,
                                 f"{total_files} archivos  |  {total_lines} lineas de codigo  |  {len(groups)} secciones")

        self.c.showPage()
        self.page_num += 1

    def draw_problem_index(self):
        """Indice alfabetico por nombre de problema (para buscar sin recordar el tema)."""
        entries = []
        section_num = 0
        for section_name, items in self.groups.items():
            section_num += 1
            for idx, item in enumerate(items):
                ref = f"{section_num}.{idx + 1}"
                extra = item["source"] or section_name
                entries.append((item["problem"], extra, ref))
        entries.sort(key=lambda e: e[0].lower())

        col_w = (PAGE_W - MARGIN_LEFT * 2 - 80) / 3
        xs = [MARGIN_LEFT + 40 + i * (col_w + 10) for i in range(3)]
        top = PAGE_H - MARGIN_TOP - 20

        self.c.setFont(TEXT_FONT_BOLD, 12)
        self.c.setFillColor(TEXT_BLACK)
        self.c.drawString(MARGIN_LEFT + 40, top, "Indice alfabetico de problemas")
        y = top - 18
        y_start = y
        col = 0
        letra = ""

        for nombre, extra, ref in entries:
            if y < MARGIN_BOTTOM + 14:
                col += 1
                if col > 2:
                    self.c.showPage()
                    self.page_num += 1
                    self.c.setFont(TEXT_FONT_BOLD, 11)
                    self.c.setFillColor(TEXT_BLACK)
                    self.c.drawString(MARGIN_LEFT + 40, top, "Indice alfabetico (cont.)")
                    col = 0
                    y_start = top - 18
                y = y_start

            if nombre[:1].upper() != letra:
                letra = nombre[:1].upper()
                self.c.setFont(TOC_FONT_BOLD, TOC_SIZE)
                self.c.setFillColor(BG_MID)
                self.c.drawString(xs[col], y, letra)
                y -= 10

            self.c.setFont(TOC_FONT, TOC_SIZE - 1.5)
            self.c.setFillColor(TEXT_BLACK)
            self.c.drawString(xs[col] + 6, y, nombre[:34])

            self.c.setFillColor(TEXT_LIGHT)
            self.c.drawRightString(xs[col] + col_w - 22, y, extra[:12])
            self.c.setFillColor(TEXT_GRAY)
            self.c.drawRightString(xs[col] + col_w, y, ref)

            y -= 9.5

    def generate(self, silencioso=False):
        if not silencioso:
            print(f"  Generando notebook con "
                  f"{sum(len(v) for v in self.groups.values())} archivos...")

        # Hoja de reparto, antes que todo lo demas
        self.draw_asignacion()

        # Portada/TOC
        self.draw_cover(self.groups)

        # Contenido
        section_num = 0
        for section_name, items in self.groups.items():
            section_num += 1
            self.draw_section_title(section_num, section_name)

            for idx, item in enumerate(items):
                sub_num = f"{section_num}.{idx + 1}"
                bookmark_key = f"sec_{section_num}_{idx}"
                self.draw_subsection_title(
                    sub_num,
                    item["label"],
                    item["description"],
                    item["path"],
                    bookmark_key,
                )
                if section_name == "Formulario":
                    self.draw_formulario(item["code"])
                else:
                    self.draw_code(item["code"])

        self._draw_header()
        self.c.showPage()
        self.page_num += 1
        self.draw_problem_index()

        self._draw_header()
        self.c.save()

        # Ahora agregar los links del TOC apuntando a los bookmarks
        self._add_toc_links()

        if not silencioso:
            print(f"  PDF generado: {self.output_path}")
            print(f"  Paginas: {self.page_num + 1}")

    def _add_toc_links(self):
        """Agrega links internos en la pagina del TOC hacia cada seccion."""
        from pypdf import PdfReader, PdfWriter
        from pypdf.generic import (
            ArrayObject, DictionaryObject, FloatObject,
            NameObject, TextStringObject, NumberObject,
            IndirectObject
        )

        reader = PdfReader(self.output_path)
        writer = PdfWriter()

        # Copiar todas las paginas
        for page in reader.pages:
            writer.add_page(page)

        # Copiar metadata
        if reader.metadata:
            writer.add_metadata({
                "/Title": "Notebook - " + UNIVERSITY,
                "/Author": UNIVERSITY,
            })

        for toc_page_idx, (x1, y1, x2, y2), bookmark_key in self.toc_links:
            # Buscar el bookmark destino
            if bookmark_key not in self.bookmarks:
                continue
            if toc_page_idx >= len(writer.pages):
                continue

            dest_page_idx, dest_y = self.bookmarks[bookmark_key]
            if dest_page_idx >= len(writer.pages):
                continue

            toc_page = writer.pages[toc_page_idx]
            dest_page = writer.pages[dest_page_idx]

            # Crear link annotation
            link = DictionaryObject()
            link.update({
                NameObject("/Type"): NameObject("/Annot"),
                NameObject("/Subtype"): NameObject("/Link"),
                NameObject("/Rect"): ArrayObject([
                    FloatObject(x1), FloatObject(y1),
                    FloatObject(x2), FloatObject(y2),
                ]),
                NameObject("/Border"): ArrayObject([
                    NumberObject(0), NumberObject(0), NumberObject(0),
                ]),
                NameObject("/Dest"): ArrayObject([
                    dest_page.indirect_reference,
                    NameObject("/XYZ"),
                    FloatObject(0),
                    FloatObject(dest_y + 10),
                    FloatObject(0),
                ]),
            })

            # Agregar la annotation a la pagina del TOC
            if "/Annots" not in toc_page:
                toc_page[NameObject("/Annots")] = ArrayObject()
            toc_page[NameObject("/Annots")].append(
                writer._add_object(link)
            )

        # Guardar
        with open(self.output_path, "wb") as f:
            writer.write(f)


# ──────────────────────────── MAIN ───────────────────────────────────

def main():
    print("=" * 60)
    print("  COMPETITIVE PROGRAMMING NOTEBOOK GENERATOR")
    print("=" * 60)
    print()

    try:
        import reportlab
        import pypdf
    except ImportError as e:
        print(f"  ERROR: Falta dependencia: {e}")
        print("  Ejecuta: pip install reportlab pypdf")
        input("\nPresiona Enter para salir...")
        sys.exit(1)

    print("[1/3] Escaneando archivos del repositorio...")
    entries = scan_files(REPO_ROOT)
    if not entries:
        print("  No se encontraron archivos de codigo.")
        input("\nPresiona Enter para salir...")
        sys.exit(1)

    print(f"  Encontrados: {len(entries)} archivos")
    for e in entries:
        print(f"    - {e['path']}  [{e['topic']} / {e['subtopic']}]")
    print()

    print("[2/3] Agrupando por tema...")
    groups = group_by_topic(entries)
    for section, items in groups.items():
        subtopics = ", ".join(i["subtopic"] for i in items)
        print(f"    {section}: {subtopics}")
    print()

    print("[3/3] Generando PDF...")
    # Dos pasadas. En la primera no se sabe en que pagina cae cada subtitulo
    # (depende de cuanto ocupe todo lo anterior), asi que se genera un PDF
    # desechable solo para medirlo, y la segunda ya escribe los numeros en el
    # indice. El hueco del numero se reserva igual en las dos pasadas, por eso
    # la segunda no corre nada de lugar.
    borrador = REPO_ROOT / ".notebook_pasada1.pdf"
    medicion = NotebookPDF(borrador, groups)
    medicion.generate(silencioso=True)
    page_of = {k: idx + 1 for k, (idx, _y) in medicion.bookmarks.items()}
    try:
        borrador.unlink()
    except OSError:
        pass

    pdf = NotebookPDF(OUTPUT_FILE, groups, page_of=page_of)
    pdf.generate()

    print()
    print("=" * 60)
    print("  LISTO!")
    print(f"  Archivo: {OUTPUT_FILE}")
    print("=" * 60)
    input("\nPresiona Enter para salir...")


if __name__ == "__main__":
    main()
