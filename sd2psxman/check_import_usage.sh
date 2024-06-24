
RED='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color
IMPORTS=$(grep -Eo "I_[a-zA-Z0-9_-]*" src/imports.lst | sed 's/^I_//')
#echo $IMPORTS

for a in $IMPORTS
do
    grep -r -q --include="*.c" "$a" "src/"
    if (($? == 1));
    then
        echo -e ${RED}-- IMPORT ${YELLOW}"$a"${RED} NOT FOUND IN C SOURCE${NC}
        x=1
    fi
done
