# recupera la carpeta de assets del Dropbox y la copia

chmod a+x setup.sh

# Si existe el directorio se elimina
if [ -d assets ]
then
    rm -r assets
fi

# Se crea la carpeta
mkdir assets

# Se recuperan los archivos
wget -O ficheros "https://www.dropbox.com/scl/fo/4sfp0pnbfl5dv9jfs0ini/h?rlkey=158jomg259o0a6efywppjnjxq&dl=0"

unzip ficheros

rm ficheros

mv mapas                    assets/mapas
mv animaciones              assets/animaciones


# LIBRERIAS

#cd lib
#unzip assimp
# rm assimp.zip