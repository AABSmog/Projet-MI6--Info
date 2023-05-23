### Magasin des boissons
Bienvenue dans votre magasin de boissons XYZ, le projet se compose d'un mode gestion qui n'est accessible qu'avec un code gestionnaire (123321 ou 987789), et d'un mode achat accessible à tout le monde.
### Fonctionnalités 
-	Mode gestion : une fois le code d’accès est saisi, le programme affiche tous les produits qui sont en rupture de stock, et les 5 produits avec le stock le plus faible (hors 0). Après, vous avez le choix de chercher un produit en utilisant son nom, chercher un produit en utilisant sa référence, modifier le stock d’un produit, ajouter un produit au stock ou quitter le programme. 
-	Mode achat : quand vous y accédez, le programme vous demande de soi créer un compte, se connecter, supprimer votre compte ou quitter le programme. Une fois votre compte est créé, vous devriez vous connecter en utilisant l’ID générée par le programme. Après, le programme vous donne le choix d’afficher les produits disponibles dans le magasin, acheter un produit, afficher vos 3 derniers achats ou quitter le programme d’achat.
-   Concernant les informations des produits :
   -    Chaque produit est composé d'un nom, référence, quantité, prix et taille.
   -    Pour le nom du produit, si vous souhaitez chercher un produit en l'utilisant, veuillez écrire   le nom du produit sans espaces (Par exemple, Coca Cola == Cocacola).
   -    Pour la référence, elle doit être comprise entre 1000 et 10000.
   -    Pour la quantité et le prix, ils doivent être strictement positifs.
   -    Pour la taille, elle doit être soi 1 (petit), soi 2 (moyen) ou soi 3 (grand).
### Utilisation
Compiler le programme en utilisant le makefile.
-	Ouvrez votre terminal Linux.
-	Accéder au répertoire ou se trouve le makefile et l’ensemble des codes utilisés pour le programme.
-	 Tapez  ‘make’
-	Tapez  ./myshop 
### Auteurs
-	Hamza EL KARCHOUNI
-	Allan SOUGANI KONE
-	Assane BOUSSO