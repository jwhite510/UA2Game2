:set makeprg=./get_build_errors.sh

au bufenter *.h :compiler unreal422
au bufenter *.cpp :compiler unreal422
