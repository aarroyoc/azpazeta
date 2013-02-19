CPP_FILE_LIST=`find ../src -name '*.cpp' -print`
xgettext -d azpazeta -s --keyword=_ -o azpazeta.pot $CPP_FILE_LIST
