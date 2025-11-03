#!/bin/bash
# PDF generation script for competitive programming reference
# Adapted from https://github.com/Laakeri/contestlib

set -e

cd "$(dirname "$0")/.."
ROOT_DIR="$(pwd)"
PDF_DIR="$ROOT_DIR/pdf"
OUTPUT_FILE="contestlib.pdf"

echo "Generating PDF reference document..."

# Create main.tex
cat "$PDF_DIR/header.tex" > "$PDF_DIR/main.tex"

# Function to add a section with files
add_section() {
    local section_name="$1"
    local dir_path="$2"
    
    if [ ! -d "$dir_path" ]; then
        return
    fi
    
    # Find all .cpp files (excluding tests)
    local files=$(find "$dir_path" -maxdepth 1 -name "*.cpp" -not -path "*/test*" | sort)
    
    if [ -z "$files" ]; then
        return
    fi
    
    echo "Adding section: $section_name"
    echo "\\section{$section_name}" >> "$PDF_DIR/main.tex"
    
    while IFS= read -r file; do
        if [ -f "$file" ]; then
            local filename=$(basename "$file")
            echo "  - $filename"
            
            echo "\\subsection{$filename}" >> "$PDF_DIR/main.tex"
            echo "\\begin{minted}[fontsize=\\tiny]{cpp}" >> "$PDF_DIR/main.tex"
            cat "$file" >> "$PDF_DIR/main.tex"
            echo "\\end{minted}" >> "$PDF_DIR/main.tex"
            echo "" >> "$PDF_DIR/main.tex"
        fi
    done <<< "$files"
}

# Add sections for each category
add_section "Data Structures" "datastruct"
add_section "Graph Algorithms" "graph"
add_section "Mathematics" "math"
add_section "String Algorithms" "string"
add_section "Miscellaneous" "misc"

# Add footer
cat "$PDF_DIR/footer.tex" >> "$PDF_DIR/main.tex"

echo ""
echo "Running pdflatex (this may take a few moments)..."

# Change to PDF directory for compilation
cd "$PDF_DIR"

# Run pdflatex with -shell-escape (required for minted)
# Run twice for proper table of contents
# Don't exit on non-zero return (pdflatex can return non-zero even on success with warnings)
set +e
pdflatex -shell-escape -interaction=nonstopmode main.tex > /dev/null 2>&1
pdflatex -shell-escape -interaction=nonstopmode main.tex > /dev/null 2>&1
set -e

# Move PDF to root and clean up
if [ -f "main.pdf" ]; then
    mv main.pdf "$ROOT_DIR/$OUTPUT_FILE"
    echo ""
    echo "Success! PDF generated at: $OUTPUT_FILE"
    
    # Clean up auxiliary files
    rm -f main.tex main.aux main.log main.toc main.out
    rm -rf _minted-main
else
    echo "Error: PDF generation failed"
    exit 1
fi
