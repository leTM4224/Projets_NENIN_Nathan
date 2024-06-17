# Nouvelle version
client=$(grep "Client=" config.txt | cut -d '=' -f2)
produit=$(grep "Produit=" config.txt | cut -d '=' -f2)
version=$(grep "Version=" config.txt | cut -d '=' -f2)

major=$(echo $version | cut -d '.' -f1)
minor=$(echo $version | cut -d '.' -f2)
build=$(echo $version | cut -d '.' -f3)

case $1 in
    --major)
        major=$((major+1))
        minor=0
        build=0
        ;;
    --minor)
        minor=$((minor+1))
        build=0
        ;;
    --build)
        build=$((build+1))
        ;;
    *)
        echo "Paramètre invalide. Utilisez --major, --minor, ou --build."
        exit 1
        ;;
esac

nouvelle_version="$major.$minor.$build"

echo -e "Client=$client\nProduit=$produit\nVersion=$nouvelle_version" > config.txt

# Creation du volume et lancement du conteneur clock
current_dir=$(pwd)
mkdir $current_dir/sae103
docker container run --name sae103-forever -v $current_dir/sae103:/work -d bigpapoo/clock

# Monte tout les fichiers dans le volume
for fich in *.c
do
    docker cp $fich sae103-forever:/work
done
docker cp gendoc-user.php sae103-forever:/work
docker cp gendoc-tech.php sae103-forever:/work
docker cp DOC_UTILISATEUR.md sae103-forever:/work

# Generation des fichiers HTML
docker container run --rm -v $current_dir/sae103:/work -t bigpapoo/sae103-php php /work/gendoc-user.php
docker container run --rm -v $current_dir/sae103:/work -t bigpapoo/sae103-php php /work/gendoc-tech.php
# Generation des fichiers PDF
docker container run --rm -v $current_dir/sae103:/work -t bigpapoo/sae103-html2pdf "html2pdf DOC_UTILISATEUR.html DOC_UTILISATEUR.pdf"
docker container run --rm -v $current_dir/sae103:/work -t bigpapoo/sae103-html2pdf "html2pdf DOC_TECHNIQUE.html DOC_TECHNIQUE.pdf"

# Compression en TGZ
docker container exec sae103-forever tar czvf "$client"-$nouvelle_version.tgz -C /work /work
# Recuperation des fichiers
docker cp sae103-forever:/"$client"-$nouvelle_version.tgz ./

# Arret du conteneur et suppression du volume
docker container stop sae103-forever
docker container rm sae103-forever
rm -rf $current_dir/sae103
