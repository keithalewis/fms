MKDN = $(wildcard *.md)
HTML = $(MKDN:.md=.html)
FLAGS = -s # smart quotes
FLAGS += --mathjax
FLAGS += --css ftap.css
FLAGS += --section-divs
FLAGS += -H header.html
FLAGS += -f markdown+tex_math_single_backslash+auto_identifiers

all: ftapm.html

$(HTML): %.html: %.md
	pandoc $(FLAGS) $< -o $@

rsync: $(HTML)
	rsync ftap.css ftap.html $(HTML) kal@web69.webfaction.com:webapps/kalx/

clean:
	rm -f $(HTML)
