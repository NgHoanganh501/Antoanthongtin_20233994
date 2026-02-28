def normalize(s):
    t = ""
    for c in s.upper():
        if c.isalpha():
            if c == "J":
                c = "I"       #  I/J gộp chung
            t += c
    return t

def build_table(key):
    key = normalize(key)
    used = set("J")
    seq = []

    # Thêm keyword vào trước
    for ch in key:
        if ch not in used:
            used.add(ch)
            seq.append(ch)

    # Thêm các chữ còn lại của alphabet
    for ch in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
        if ch not in used:
            used.add(ch)
            seq.append(ch)

    # Tạo 5x5
    grid = [seq[i*5:(i+1)*5] for i in range(5)]
    pos = {grid[r][c]: (r, c) for r in range(5) for c in range(5)}
    return grid, pos

def print_table_linear(grid):
    print("Playfair Matrix (linear):", "".join("".join(row) for row in grid))

def make_pairs(msg):
    msg = normalize(msg)
    res = ""
    i = 0

    while i < len(msg):
        a = msg[i]
        b = msg[i+1] if i+1 < len(msg) else "X"

        if a == b:
            res += a + "X"
            i += 1
        else:
            res += a + b
            i += 2

    if len(res) % 2:
        res += "X"

    return res

def encrypt(msg, key):
    grid, pos = build_table(key)
    pairs = make_pairs(msg)
    out = ""

    for i in range(0, len(pairs), 2):
        a, b = pairs[i], pairs[i+1]
        r1, c1 = pos[a]
        r2, c2 = pos[b]

        if r1 == r2:
            out += grid[r1][(c1+1) % 5]
            out += grid[r2][(c2+1) % 5]
        elif c1 == c2:
            out += grid[(r1+1) % 5][c1]
            out += grid[(r2+1) % 5][c2]
        else:
            out += grid[r1][c2]
            out += grid[r2][c1]

    return out

def decrypt(cipher, key):
    grid, pos = build_table(key)
    out = ""

    for i in range(0, len(cipher), 2):
        a, b = cipher[i], cipher[i+1]
        r1, c1 = pos[a]
        r2, c2 = pos[b]

        if r1 == r2:
            out += grid[r1][(c1-1) % 5]
            out += grid[r2][(c2-1) % 5]
        elif c1 == c2:
            out += grid[(r1-1) % 5][c1]
            out += grid[(r2-1) % 5][c2]
        else:
            out += grid[r1][c2]
            out += grid[r2][c1]

    return out


key = input("Enter keyword: ")
plaintext = input("Enter plaintext: ")

grid, pos = build_table(key)

print_table_linear(grid)

cipher = encrypt(plaintext, key)
print("Ciphertext:", cipher)

decoded = decrypt(cipher, key)
print("Decrypted :", decoded)