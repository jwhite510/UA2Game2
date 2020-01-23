#!/bin/bash
# find -L ./classes -name \*.h -exec ctags --c++-kinds=+p {} +
ctags -R --c++-kinds=+p .

