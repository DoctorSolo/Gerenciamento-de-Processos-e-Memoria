Saída Gerada:



----- SIMULACAO DE PARTICIONAMENTO CONTIGUO -----



First Fit Allocation:

Processo 1 (30 blocos) alocado com sucesso

Processo 2 (20 blocos) alocado com sucesso

Processo 3 (40 blocos) alocado com sucesso

Processo 4 (10 blocos) alocado com sucesso

Falha ao alocar Processo 5 (25 blocos)



Mapa da Memoria:

Particao 0: \[0-29] Processo 1 (30 blocos)

Particao 1: \[30-49] Processo 2 (20 blocos)

Particao 2: \[50-89] Processo 3 (40 blocos)

Particao 3: \[90-99] Processo 4 (10 blocos)



\[... resultados similares para Best Fit e Worst Fit ...]



----- SIMULACAO DE PAGINACAO -----



Tabela de Paginas:

Quadro  Processo        Pagina

0       1               0

1       1               1

\[...]

14      1               14

15      2               0

\[...]

22      2               7

23      3               0

\[...]

29      3               6



Análise de Eficiência dos Algoritmos

Particionamento Contíguo:


First Fit:



&nbsp;   Funcionamento: Aloca no primeiro bloco livre que seja grande o suficiente



&nbsp;   Vantagens:



&nbsp;       Simplicidade de implementação



&nbsp;       Rapidez na alocação (poucas comparações necessárias)



&nbsp;   Desvantagens:



&nbsp;       Pode criar fragmentação externa no início da memória



&nbsp;       Não é o mais eficiente em utilização de espaço



&nbsp;   Complexidade: O(n) para cada alocação



Best Fit:



&nbsp;   Funcionamento: Aloca no menor bloco livre que seja grande o suficiente



&nbsp;   Vantagens:



&nbsp;       Minimiza o desperdício de espaço (fragmentação interna)



&nbsp;       Melhor utilização da memória em cenários com muitos pequenos processos



&nbsp;   Desvantagens:



&nbsp;       Requer busca completa na lista de partições



&nbsp;       Pode criar muitos pequenos fragmentos inúteis



&nbsp;   Complexidade: O(n) para cada alocação (mas com mais comparações que First Fit)



Worst Fit:



&nbsp;   Funcionamento: Aloca no maior bloco livre disponível



&nbsp;   Vantagens:



&nbsp;       Deixa blocos grandes livres para futuros processos grandes



&nbsp;       Reduz a criação de pequenos fragmentos



&nbsp;   Desvantagens:



&nbsp;       Pode desperdiçar memória em processos pequenos



&nbsp;       Não é eficiente para cenários com muitos processos pequenos



&nbsp;   Complexidade: O(n) para cada alocação







Paginação:



Alocação por Paginação:



&nbsp;   Funcionamento: Divide memória em quadros fixos e processos em páginas



&nbsp;   Vantagens:



&nbsp;       Elimina a fragmentação externa



&nbsp;       Permite alocação não-contígua



&nbsp;       Mais flexível que particionamento



&nbsp;   Desvantagens:



&nbsp;       Overhead da tabela de páginas



&nbsp;       Pode ter fragmentação interna (última página)



&nbsp;   Complexidade: O(n) para alocação, mas constante para acesso







Cenários de Aplicação:



&nbsp;   First Fit é ideal quando:



&nbsp;       Velocidade de alocação é crítica



&nbsp;       A ordem dos processos é bem conhecida e organizada



&nbsp;   Best Fit funciona melhor quando:



&nbsp;       Há muitos processos pequenos



&nbsp;       A memória é limitada e precisa ser bem aproveitada



&nbsp;   Worst Fit é adequado para:



&nbsp;       Sistemas com processos grandes



&nbsp;       Quando se quer evitar fragmentação pequena



&nbsp;   Paginação é superior quando:



&nbsp;       Há necessidade de compartilhamento de memória



&nbsp;       Sistemas com memória virtual



&nbsp;       Quando a alocação contígua é problemática







Recomendações:



&nbsp;   Para sistemas com processos de tamanhos variados, a paginação geralmente oferece o melhor equilíbrio entre desempenho e utilização de memória.



&nbsp;   Em sistemas embarcados ou com restrições de hardware, o Best Fit pode ser preferível por sua melhor utilização de memória.



&nbsp;   Em sistemas em tempo real onde a velocidade de alocação é crucial, o First Fit pode ser a melhor opção.



&nbsp;   O Worst Fit tem aplicações mais específicas e geralmente não é a primeira escolha para sistemas gerais.



Este relatório demonstra que a escolha do algoritmo ideal depende fortemente do padrão de alocação de memória específico de cada sistema e das prioridades do projeto (velocidade vs. utilização de memória).





