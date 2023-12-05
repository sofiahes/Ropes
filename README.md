# Ropes
Ropes es una estructura de datos de tipo **b+ tree "combinada" con un patricia trie**. <br>
La diferencia entre estos es que los Ropes presentan una manera diferente de almacenar data de tipo string en árboles b+ <br>
Tiene una ventaja sobre la estructura strings y también sobre otras grandes como Tries, Linked List y Árboles B+, si queremos lograr manejar y hacer operaciones con strings de un tamaño largo, usar ropes es una alternativa que destaca sobre las demás por su complejidad. <br>
<br>
La representación natural es un árbol b+, donde cada nodo interno representa la concatenación de sus hijos, y las hojas son cadenas enteras. <br>
<br>
Este trabajo contiene operaciones de **insertar, eliminar, split, concatenación, buscar y "reverse"**. <br>
Con ello, se muestra un ejemplo del output con 2 oraciones: "Habra el curso de" y "ADA_EN_VERANO"; <br>
![Output.](/Ropesoutput.png)
