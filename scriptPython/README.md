# Script de Migración: listings → minted

## Propósito
Automatiza la migración de 5 archivos `main.tex` (LaTeX) del paquete `listings` a `minted` para los laboratorios de ADA (Unidad 2 y 3).

## Archivos objetivo
| Unidad | Laboratorio | Ruta |
|--------|-------------|------|
| 2 | 04 | `Unidad2/lab04/TeX/main.tex` |
| 2 | 06 | `Unidad2/lab06/TeX/main.tex` |
| 3 | 07 | `Unidad3/lab07/TeX/main.tex` |
| 3 | 08 | `Unidad3/lab08/TeX/main.tex` |
| 3 | 09 | `Unidad3/lab09/TeX/main.tex` |

## Requisitos
- Python 3.8+
- Ejecutar desde la carpeta base: `/home/camiloasd/Documentos/VS/labADA/`

## Flujo de funcionamiento (9 transformaciones)

| Paso | Acción | Regex / Método |
|------|--------|----------------|
| 1 | Reemplazar **primer** `\usepackage{listings}` por `\usepackage{minted}` | `re.sub(..., count=1)` |
| 2 | Eliminar `\lstdefinestyle{ascii-tree}{...}` | `re.sub(r'\\lstdefinestyle\{ascii-tree\}\{[^}]*\}', '')` |
| 3 | Eliminar **primer** `\lstset{basicstyle=\ttfamily,...}` | `re.sub(..., count=1)` |
| 4 | Eliminar **segundo** `\usepackage{listings}` | `re.sub(..., count=1)` |
| 5 | Eliminar **segundo** bloque `\lstset{frame=tb,...}` (multi-línea, hasta `backgroundcolor=\color{codebackground}`) | `re.sub(..., flags=re.DOTALL)` |
| 6 | Insertar bloque `\setminted{...}` **después** de `\definecolor{codebackground}{rgb}{0.95, 0.95, 0.92}` | `re.sub` con callback `insert_minted` |
| 7 | Reemplazar 5× `\lstinputlisting[language=c++,numbers=left,?]{../e-n/eX.cpp}` por `\inputminted{cpp}{../e-n/eX.cpp}` | `re.sub` (acepta coma opcional) |
| 8 | Limpiar llave suelta `  }` que queda tras `\usepackage{minted}` | `str.replace` |
| 9 | Normalizar líneas en blanco (máx. 2 consecutivas) | `re.sub(r'\n{3,}', '\n\n')` |

## Uso

```bash
cd /home/camiloasd/Documentos/VS/labADA
python3 scriptPython/migrate_to_minted.py
# O si se dieron permisos de ejecución:
./scriptPython/migrate_to_minted.py
```

## Verificación post-migración

```bash
# Verificar que cada archivo tiene 5 inputminted
grep -c "inputminted" Unidad2/lab04/TeX/main.tex Unidad2/lab06/TeX/main.tex Unidad3/lab07/TeX/main.tex Unidad3/lab08/TeX/main.tex Unidad3/lab09/TeX/main.tex

# Verificar que no quedan rastros de listings
grep -n "lstset\|lstdefinestyle\|lstinputlisting\|usepackage.*listings" Unidad2/lab04/TeX/main.tex Unidad2/lab06/TeX/main.tex Unidad3/lab07/TeX/main.tex Unidad3/lab08/TeX/main.tex Unidad3/lab09/TeX/main.tex

# Compilar (requiere -shell-escape para minted)
cd Unidad2/lab04/TeX && pdflatex -shell-escape main.tex
```

## Configuración `minted` aplicada

```latex
\setminted{%
  fontsize=\small,        % Tamaño de letra pequeño
  breaklines,             % Salto automático de líneas
  breakanywhere,          % Permite romper en cualquier carácter
  linenos,                % Números de línea
  numbersep=6pt,          % Separación números-código
  frame=lines,            % Marco (líneas arriba/abajo)
  framesep=3mm,           % Separación marco-código
  baselinestretch=1,      % Interlineado
  bgcolor=codebackground, % Color de fondo (rgb 0.95,0.95,0.92)
  tabsize=3               % Tabulación = 3 espacios
}
```

## Notas
- El script es **idempotente**: ejecutarlo varias veces no duplica cambios.
- `lab05` **ya estaba migrado** y no se toca.
- La configuración `codebackground` debe estar definida en el preámbulo (lo está en todos los archivos).