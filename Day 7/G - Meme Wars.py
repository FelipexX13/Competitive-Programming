dic = {
    1: "a",
    2: "b",
    4: "c",
    8: "d",
    16: "e",
    32: "f",
    64: "g",
    128: "h",
    256: "i",
    512: "j",
    1024: "k",
    2048: "l",
    4096: "m",
    8192: "n",
    16384: "o",
    32768: "p",
    65536: "q",
    131072: "r",
    262144: "s",
    524288: "t",
    1048576: "u",
    2097152: "v",
    4194304: "w",
    8388608: "x",
    16777216: "y",
    33554432: "z"
}
n = int(input())
cual = 1
for clave,valor in dic.items():
    if(n%clave == 0):
        cual = clave
        continue
    else:
        print(dic[cual])
        break
