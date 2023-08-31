#!/bin/bash 

# Compilez votre programme C si nécessaire (vous pouvez le commenter car le programme est déjà compilé)
# gcc -o main main.c

k=0
echo "Toutes les exécutions démarrent."

# Boucle pour chaque nombre d'execution
for ((  k=0; k< 5; k++ )); do
    for size in 3 4 5 6 7; do
        ./main $size
    done
done

echo "Toutes les exécutions sont terminées."
