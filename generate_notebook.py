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
from collections import OrderedDict

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
COACH = "Juan Jose Betancourt Lozano"
UNIVERSITY = "Universidad de Ibague"

# Orden de las secciones (basado en el indice del cpp.pdf de la UFPS)
SECTION_ORDER = [
    "Data Structures",
    "Dynamic Programming",
    "Geometry",
    "Graph",
    "Math",
    "String",
    "Greedy",
    "Implementation",
]

# Layout
PAGE_W, PAGE_H = landscape(letter)  # 792 x 612 pts
MARGIN_TOP = 36
MARGIN_BOTTOM = 28
MARGIN_LEFT = 36
MARGIN_RIGHT = 36
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

        entries.append({
            "name": fp.stem,
            "topic": topic,
            "subtopic": subtopic,
            "description": description,
            "code": "\n".join(code_lines),
            "path": str(fp.relative_to(root)),
            "extension": fp.suffix,
        })

    return entries


def group_by_topic(entries):
    """Agrupa entradas por tema en el orden definido."""
    groups = OrderedDict()
    for section in SECTION_ORDER:
        group = [e for e in entries if e["topic"] == section]
        if group:
            groups[section] = sorted(group, key=lambda e: e["subtopic"].lower())

    known = set(SECTION_ORDER)
    extra = sorted(set(e["topic"] for e in entries if e["topic"] not in known))
    for topic in extra:
        group = [e for e in entries if e["topic"] == topic]
        if group:
            groups[topic] = sorted(group, key=lambda e: e["subtopic"].lower())

    return groups


# ───────────────────────── GENERADOR DE PDF ──────────────────────────

class NotebookPDF:
    def __init__(self, output_path, groups):
        self.output_path = str(output_path)
        self.groups = groups
        self.c = canvas.Canvas(self.output_path, pagesize=landscape(letter))
        self.c.setTitle("Notebook - " + UNIVERSITY)
        self.c.setAuthor(UNIVERSITY)
        self.page_num = 0

        self.col_width = (PAGE_W - MARGIN_LEFT - MARGIN_RIGHT - COL_GAP) / 2
        self.content_top = PAGE_H - MARGIN_TOP
        self.content_bottom = MARGIN_BOTTOM

        self.col = 0
        self.y = self.content_top

        # Bookmarks para links del TOC
        self.bookmarks = {}  # key -> (page_index, y_pos)
        self._page_index = 1  # pagina 0 = cover

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
        self._page_index += 1
        self.col = 0
        self.y = self.content_top

    def _draw_header(self):
        # Header bar negro
        self.c.setFillColor(BG_DARK)
        self.c.rect(0, PAGE_H - 18, PAGE_W, 18, fill=True, stroke=False)
        self.c.setFillColor(TEXT_WHITE)
        self.c.setFont(HEADER_FONT, HEADER_SIZE)
        self.c.drawString(MARGIN_LEFT, PAGE_H - 13.5,
                          f"{UNIVERSITY}  -  NOTEBOOK")
        self.c.drawRightString(PAGE_W - MARGIN_RIGHT, PAGE_H - 13.5,
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

    def draw_subsection_title(self, number, subtopic, desc, path, bookmark_key):
        needed = 12
        if desc:
            max_chars = int(self.col_width / (DESC_SIZE * 0.48))
            desc_lines = len(desc) // max_chars + 1
            needed += desc_lines * (DESC_SIZE + 2) + 2

        self.ensure_space(needed + CODE_LEADING * 3)
        x = self.col_x()

        # Registrar posicion para el link del TOC
        self.bookmarks[bookmark_key] = (self._page_index, self.y)

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
            max_chars = int(self.col_width / (DESC_SIZE * 0.42))
            words = desc.split()
            line = ""
            for word in words:
                test = (line + " " + word).strip()
                if len(test) > max_chars:
                    self.c.drawString(x + 2, self.y - 1, line)
                    self.y -= DESC_SIZE + 2
                    line = word
                else:
                    line = test
            if line:
                self.c.drawString(x + 2, self.y - 1, line)
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

    def draw_cover(self, groups):
        """Portada con info del equipo y TOC con links."""
        # ---- HEADER OSCURO ----
        self.c.setFillColor(BG_DARK)
        self.c.rect(0, PAGE_H - 70, PAGE_W, 70, fill=True, stroke=False)

        # Nombre del concurso
        self.c.setFillColor(TEXT_WHITE)
        self.c.setFont(TEXT_FONT_BOLD, 13)
        self.c.drawCentredString(PAGE_W / 2, PAGE_H - 28, CONTEST_NAME)

        # Linea decorativa
        dash_text = " - " * 22
        self.c.setFont(TEXT_FONT, 8)
        self.c.setFillColor(HexColor("#888888"))
        self.c.drawCentredString(PAGE_W / 2, PAGE_H - 43, dash_text + "NOTEBOOK" + dash_text)

        # Universidad
        self.c.setFont(TEXT_FONT_BOLD, 11)
        self.c.setFillColor(TEXT_WHITE)
        self.c.drawCentredString(PAGE_W / 2, PAGE_H - 60, UNIVERSITY)

        # ---- INFO DEL EQUIPO ----
        info_y = PAGE_H - 95

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
        self.c.drawRightString(PAGE_W - MARGIN_RIGHT - 40, PAGE_H - 95,
                               datetime.date.today().strftime("%B %d, %Y"))

        # ---- TABLA DE CONTENIDOS ----
        toc_y = PAGE_H - 210
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

        section_num = 0
        total_entries = sum(1 + len(items) for items in groups.values())
        entry_count = 0
        half = total_entries // 2

        # Guardar posiciones de los links para aplicar despues
        self.toc_links = []

        for section_name, items in groups.items():
            section_num += 1

            if entry_count >= half and toc_x == toc_x_left:
                toc_x = toc_x_right
                toc_y = toc_y_start

            # Titulo de seccion
            self.c.setFont(TOC_FONT_BOLD, TOC_SIZE)
            self.c.setFillColor(BG_MID)
            self.c.drawString(toc_x, toc_y, f"{section_num}  {section_name}")
            toc_y -= 12
            entry_count += 1

            for idx, item in enumerate(items):
                if toc_y < MARGIN_BOTTOM + 30:
                    toc_x = toc_x_right
                    toc_y = toc_y_start

                sub_num = f"{section_num}.{idx + 1}"
                label = f"    {sub_num}  {item['subtopic']}"

                self.c.setFont(TOC_FONT, TOC_SIZE - 1)
                self.c.setFillColor(TEXT_GRAY)
                self.c.drawString(toc_x + 8, toc_y, label)

                # Dots
                dots_x = toc_x + toc_col_width - 10
                text_width = self.c.stringWidth(label, TOC_FONT, TOC_SIZE - 1)
                dot_start = toc_x + 8 + text_width + 4
                if dot_start < dots_x - 10:
                    num_dots = int((dots_x - dot_start) / 3)
                    self.c.setFillColor(SEPARATOR_COLOR)
                    self.c.drawString(dot_start, toc_y, "." * num_dots)

                # Guardar info del link para aplicar despues de generar bookmarks
                bookmark_key = f"sec_{section_num}_{idx}"
                link_rect = (toc_x + 8, toc_y - 2,
                             toc_x + toc_col_width, toc_y + TOC_SIZE)
                self.toc_links.append((link_rect, bookmark_key))

                toc_y -= 11
                entry_count += 1

            toc_y -= 4

        # Stats
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

    def generate(self):
        print(f"  Generando notebook con {sum(len(v) for v in self.groups.values())} archivos...")

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
                    item["subtopic"],
                    item["description"],
                    item["path"],
                    bookmark_key,
                )
                self.draw_code(item["code"])

        self._draw_header()
        self.c.save()

        # Ahora agregar los links del TOC apuntando a los bookmarks
        self._add_toc_links()

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

        # Agregar link annotations a la pagina 0 (TOC)
        toc_page = writer.pages[0]

        for (x1, y1, x2, y2), bookmark_key in self.toc_links:
            # Buscar el bookmark destino
            if bookmark_key not in self.bookmarks:
                continue

            dest_page_idx, dest_y = self.bookmarks[bookmark_key]
            if dest_page_idx >= len(writer.pages):
                continue

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
    pdf = NotebookPDF(OUTPUT_FILE, groups)
    pdf.generate()

    print()
    print("=" * 60)
    print("  LISTO!")
    print(f"  Archivo: {OUTPUT_FILE}")
    print("=" * 60)
    input("\nPresiona Enter para salir...")


if __name__ == "__main__":
    main()
