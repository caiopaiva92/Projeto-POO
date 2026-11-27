# Decisões do projeto

## 1. Por que a base é abstrata?

Porque não dá para dispensar um "produto" sem saber que tipo de medicamento ele é. O isento sai sem receita, o de tarja vermelha precisa de receita e o controlado precisa de receita e ainda tem que ser escriturado. Por isso deixei `dispensar()`, `tarja()` e `condicaoDeVenda()` como puras. Se `dispensar()` tivesse um corpo padrão, tipo liberar sem receita, um medicamento novo que eu esquecesse de sobrescrever ia ser vendido sem receita e o compilador não ia reclamar. Sendo pura, ele nem compila.

## 2. Por que cada herança é da forma que é?

Pública: todo medicamento é um produto do estoque, então os três podem ser usados onde o estoque espera um `Produto`.

Múltipla: o controlado é um produto e também tem a obrigação de escriturar as saídas com receita retida. Por isso herda de `Produto` e de `Escrituravel`. Como a interface não tem atributos, nada fica repetido.

Privada: o estoque usa um vector por dentro, mas não deveria ser mexido como um vector qualquer. Só deixei `size` e `empty`. Não deixei `push_back`, `insert` e `emplace_back`, porque aí daria para colocar um medicamento repetido sem passar pelo `adicionar()`. Não deixei `operator[]`, `at`, `front`, `back`, `begin` e `end`, porque daria para trocar ou tirar um medicamento do estoque sem controle. Não deixei `erase`, `clear` e `pop_back`, porque na farmácia o medicamento sai pelo nome, com `remover()`. E `resize`, `reserve` e `capacity` não fazem sentido para a farmácia.

## 3. Quem é dono de quê?

O `Estoque` é dono dos medicamentos, e isso aparece no tipo, porque ele guarda `std::unique_ptr<Produto>`. Quando um medicamento é removido ou quando o estoque acaba no fim do escopo, o `unique_ptr` apaga o medicamento. Como o destrutor é virtual, roda o destrutor da classe certa, e é por isso que o `vivos` chega a zero. Os `Produto*` que o `main` pega com `buscar()` só servem para acessar, eles não apagam nada. Cada medicamento é dono dos seus próprios dados, e o controlado também é dono da lista de receitas retidas.

## 4. Por que cada operador é membro ou livre?

O `operator<<` é livre porque do lado esquerdo fica o `cout`, que é um `ostream`, e essa classe não é minha. O `operator+=` é membro do `Produto` porque do lado esquerdo fica o próprio medicamento que está sendo reposto. Ele aumenta a quantidade e devolve o próprio objeto, igual ao `+=` de um `int`.