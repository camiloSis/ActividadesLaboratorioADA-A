#!/usr/bin/env python3
"""
Migración masiva: listings -> minted para reportes LaTeX de laboratorios ADA.
Procesa 5 archivos main.tex en Unidad2/lab04, lab06 y Unidad3/lab07-09.
"""

import re
from pathlib import Path

MINTED_CONFIG = r'''
\setminted{%
  fontsize=\small,
  breaklines,
  breakanywhere,
  linenos,
  numbersep=6pt,
  frame=lines,
  framesep=3mm,
  baselinestretch=1,
  bgcolor=codebackground,
  tabsize=3
}'''

FILES = [
    "Unidad2/lab04/TeX/main.tex",
    "Unidad2/lab06/TeX/main.tex",
    "Unidad3/lab07/TeX/main.tex",
    "Unidad3/lab08/TeX/main.tex",
    "Unidad3/lab09/TeX/main.tex",
]

def migrate(filepath):
    content = filepath.read_text()
    original = content

    # 1. Primer \usepackage{listings} -> \usepackage{minted}
    content = re.sub(r'\\usepackage\{listings\}', r'\\usepackage{minted}', content, count=1)

    # 2. Eliminar \lstdefinestyle{ascii-tree}{...}
    content = re.sub(r'\\lstdefinestyle\{ascii-tree\}\{[^}]*\}', '', content)

    # 3. Eliminar primer \lstset{basicstyle=...}
    content = re.sub(r'\\lstset\{basicstyle=\\ttfamily,[^}]*\}', '', content, count=1)

    # 4. Eliminar segundo \usepackage{listings}
    content = re.sub(r'\\usepackage\{listings\}', '', content, count=1)

    # 5. Eliminar segundo \lstset{frame=tb,...} (multi-línea)
    content = re.sub(
        r'\\lstset\{frame=tb,[^}]*backgroundcolor=\s*\\color\{codebackground\},\s*\}',
        '', content, flags=re.DOTALL
    )

    # 6. Insertar \setminted tras \definecolor{codebackground}
    def insert_minted(m):
        return m.group(1) + MINTED_CONFIG
    content = re.sub(
        r'(\\definecolor\{codebackground\}\{rgb\}\{0\.95,\s*0\.95,\s*0\.92\})',
        insert_minted, content
    )

    # 7. Reemplazar \lstinputlisting -> \inputminted (con/sin coma final)
    content = re.sub(
        r'\\lstinputlisting\[language=c\+\+,numbers=left,?\]\{(\.\./e-n/e[1-5]\.cpp)\}',
        r'\\inputminted{cpp}{\1}', content
    )

    # 8. Limpiar llave suelta tras \usepackage{minted}
    content = content.replace('\\usepackage{minted}\n  }', '\\usepackage{minted}')

    # 9. Limpiar líneas en blanco excesivas
    content = re.sub(r'\n{3,}', '\n\n', content)

    if content != original:
        filepath.write_text(content)
        print(f"✓ Migrado: {filepath}")
    else:
        print(f"✗ Sin cambios: {filepath}")

if __name__ == "__main__":
    base = Path("/home/camiloasd/Documentos/VS/labADA")
    for rel in FILES:
        migrate(base / rel)
    print("\nMigración completada.")