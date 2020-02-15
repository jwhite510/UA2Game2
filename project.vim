:set makeprg=./get_build_errors.sh

au bufenter *.h :compiler unreal422
au bufenter *.cpp :compiler unreal422
au bufenter *.h :set complete-=t
au bufenter *.cpp :set complete-=t
