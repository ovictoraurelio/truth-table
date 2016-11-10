# Truth Table (logic)

Este é um pequeno projeto construído para a cadeira "Lógica para programação", do curso de Engenharia da Computação no CIn - UFPE.

A proposta deste projeto é receber como entrada uma sequência N de expressões da lógica proposicional e construir suas N tabelas.

O Projeto foi feito de acordo com a seguinte especificação:
```sh

O Projeto I é um Gerador de Tabela-Verdade a partir de uma Expressão bem-formada. Para tal, haverá a necessidade que seu programa gere automaticamente a tabela-verdade, com elementos atômicos e subexpressões distintas entre si que existam na expressão bem-formada. É garantido que as expressões serão bem-formadas.

O gerador poderá ser feito nas linguagens C, C++ ou Java.

####Entrada: Nome do arquivo "Expressoes.in"

Contem várias expressões que serão avaliadas.
A 1ª linha da entrada será um número n, indicando quantas expressões precisarão ter suas entradas avaliadas. Logo a seguir teremos n linhas, onde cada uma desta possuirá uma expressão, sem espaçamento, que será a expressão a ser avaliada, conforme as regras explicitadas anteriormente. É garantido que todas as expressões são bem-formadas e, consequentemente, possuem resposta e que cada expressão possuirá menos que 200 caracteres. O aluno que não seguir as especificações dadas perderá 0,5 durante a correção, portanto prestem atenção aos nomes dos arquivos!!!

####Saída: Nome do arquivo "Expressoes.out"

Deve possuir TODAS as saídas do gerador em um único arquivo, separadas por uma linha em branco.
para cada caso de teste imprima uma linha só com "Tabela #x", onde x indica o número de caso de teste, iniciando de '1'. A partir das outras linhas, será a geração da tabela verdade.
Na primeira linha da tabela, serão impressas, primeiramente, as variáveis. Posteriormente, deverão ser impressas todas as subexpressões com a seguinte ordenação: uma string A será menor que uma string B se o tamanho de A for menor que o tamanho de B, ou, as duas havendo o mesmo tamanho, A deverá ser lexicograficamente menor que B.
Só imprima sub-expressões distintas, por exemplo, caso apareçam duas sub-expressões (x.y), a saída válida só deverá ter uma única aparição de (x.y).
Após o seu programa gerar uma tabela, ele deve imprimir três palavras: a primeira delas é "satisfativel" ou "insatisfativel" a segunda é "e" e a terceira é "tautologia" ou "refutavel", dependendo da tabela que for gerada. Depois disso, sempre deixar uma linha em branco.
É garantido que cada expressão da entrada possuirá menos de 50 subexpressões distintas não-atômicas.

Observação: Na saída, só deverão aparecer as variáveis que estão na expressão avaliada e devem seguir ordem crescente. Ou seja, se a entrada só possuir x, y e t, a saída só poderá ter essas variáveis e deve ir de 000 até 111 em ordem crescente.

```

[Victor Aurélio]: <http://victoraurelio.com>
[Victor Aurélio at CIn]: <http://cin.ufpe.br/~vags>