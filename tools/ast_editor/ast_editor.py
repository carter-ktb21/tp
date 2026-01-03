from pathlib import Path
from tkinter import Tk
from tkinter.filedialog import askopenfilename, asksaveasfilename

Tk().withdraw()

ast_path = askopenfilename(
    title="Select AST file to add loop to",
    filetypes=[("AST files", "*.ast"), ("All files", "*.*")]
)

if not ast_path:
    print("No file selected.")
    exit()

out_path = asksaveasfilename(
    title="Save modified AST as",
    defaultextension=".ast",
    filetypes=[("AST files", "*.ast"), ("All files", "*.*")]
)

if not out_path:
    print("No output file selected.")
    exit()

ast_bytes = bytearray(Path(ast_path).read_bytes())

offsets = [0x18, 0x19, 0x1A, 0x1B]

value_input = input("Enter 4 hex byte values corresponding to sample that loop should begin (space-separated, e.g., AA BB CC DD): ")
new_values = [int(x, 16) for x in value_input.strip().split()]
if len(new_values) != 4:
    print("You must enter exactly 4 new byte values.")
    exit()

for off, val in zip(offsets, new_values):
    ast_bytes[off] = val

Path(out_path).write_bytes(ast_bytes)
print(f"Wrote modified AST: {len(ast_bytes)} bytes")
