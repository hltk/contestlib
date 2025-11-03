# PDF Reference Document Generation

This folder contains scripts to generate a PDF reference document from all C++ implementations in the repository.

**Note:** The PDF generation logic has been adapted and simplified from [Laakeri's contestlib](https://github.com/Laakeri/contestlib).

## Prerequisites

- **LaTeX**: A LaTeX distribution with `pdflatex` (e.g., MacTeX on macOS, TeX Live on Linux)
- **Pygments**: Python syntax highlighting library

## Installation

### macOS

1. **Install LaTeX** (if not already installed):
   ```bash
   brew install --cask mactex
   ```
   Or download from: https://www.tug.org/mactex/

2. **Install Pygments** using uv:
   ```bash
   uv tool install pygments
   ```

### Linux

1. **Install LaTeX**:
   ```bash
   sudo apt-get install texlive-full  # Debian/Ubuntu
   # or
   sudo dnf install texlive-scheme-full  # Fedora
   ```

2. **Install Pygments** using uv:
   ```bash
   uv tool install pygments
   ```

## Usage

To generate the PDF reference document, run:

```bash
./pdf/generate.sh
```

Or from the repository root:

```bash
bash pdf/generate.sh
```

The script will:
1. Collect all `.cpp` files from `datastruct/`, `graph/`, `math/`, `string/`, and `misc/` directories
2. Organize them by category into sections
3. Generate syntax-highlighted code using the `minted` LaTeX package
4. Compile the LaTeX document (runs twice for proper table of contents)
5. Output `contestlib.pdf` in the repository root

## Customization

### Changing Layout

Edit `pdf/header.tex` to customize:
- Page size and orientation
- Margins and column settings
- Font sizes
- Header/footer content

### Adding/Removing Directories

Edit `pdf/generate.sh` and modify the `add_section` calls at the bottom:

```bash
add_section "Section Name" "directory_path"
```

### Code Highlighting Style

The minted package uses Pygments styles. To change the style, add this line to `pdf/header.tex`:

```latex
\usemintedstyle{stylename}
```

Available styles: `default`, `emacs`, `friendly`, `colorful`, `autumn`, `murphy`, `manni`, `material`, `monokai`, `perldoc`, `pastie`, `borland`, `trac`, `native`, `fruity`, `bw`, `vim`, `vs`, `tango`, `rrt`, `xcode`, `igor`, `paraiso-light`, `paraiso-dark`, `lovelace`, `algol`, `algol_nu`, `arduino`, `rainbow_dash`, `abap`, `solarized-dark`, `solarized-light`, `sas`, `stata`, `stata-light`, `stata-dark`, `inkpot`

## Troubleshooting

### Error: `pygmentize` not found

Make sure Pygments is installed and in your PATH:
```bash
which pygmentize
pygmentize -V
```

If not found, install with: `uv tool install pygments`

### Error: Package minted not found

Your LaTeX distribution might not include the minted package. Install it:
```bash
tlmgr install minted  # For TeX Live
```

### PDF has encoding issues

Ensure your `.cpp` files are UTF-8 encoded.

### Generation is slow

This is normal. The script runs `pdflatex` twice for proper cross-references, and syntax highlighting adds processing time. For a repository of this size, expect 10-30 seconds.

