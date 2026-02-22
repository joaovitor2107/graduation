# Relatório - Laboratório de Threads

**Nome**: João Vitor de Araújo Trindade
**Data**: 22/09/2025 
**Sistema**: Linux/Ubuntu 
**Processador**: 12th Gen Intel(R) Core(TM) i7-1255U

## Parte 1: Exercícios Básicos

### Exercício 1: Hello Thread

**Observações**:
- Comportamento observado ao executar múltiplas vezes: Algumas vezes ao rodar printa a função da thread criada as vezes não.
- Ordem das mensagens: Primeiro da principal depois da thread
- Explicação do comportamento: Isso ocorre pois temos uma condição de corrida, o main não espera a thread criada terminar para poder terminar, ou seja se a thread não ser executado antes de chegarmos no return ela pode não ser executada.

### Exercício 2: Sincronização com pthread_join

**Comparação com Exercício 1**:
- Diferenças observadas: Aqui garantimos que o programa so irá terminar depois da thread criada terminar de ser executada, o "Hello da thread!" sempre é executado aqui.
- Importância do pthread_join: Garante que o programa não vá ser interrompido antes da thread criada terminar, garantindo assim comportamento deterministico no programa e evitando condições de corrida.
- Consequências de não usar pthread_join: Teremos um comportamento não deterministico, com a thread nem sempre sendo executada (ou sendo parcialmente executada).

### Exercício 3: Múltiplas Threads

**Análise**:
- Ordem de execução observada: A ordem de execução varia a cada vez que rodo o código. Com maior variação entre a ordem das threads do meio (mas todas variam algumas com menos frequencia).
- Determinismo (ou falta dele): Aqui garantimos que todas threads serão executadas, contudo não garantimos a ordem em que elas serão executadas.
- Comportamento com 100 threads: Ainda há uma aleatorização da ordem dos resultados, mas em geral os resultados saem muito proximos de estarem em ordem crescente de 0 a 99.

## Parte 2: Comunicação entre Threads

### Exercício 4: Passagem de Argumentos

**Análise**:
- Importância de ter argumentos separados para cada thread: Porque assim cada thread pode processar diferentes dados.
- Como o array garante que cada thread recebe seu próprio valor: Porque ao passar os dados para a função pthread_create, garantimos que vai ser passado o argumento i para a thread de numero i, e podemos fazer isso graças a forma como os dados são estruturados em array.
- Processo de conversão de tipos (cast) observado: Convertamos um ponteiro do void (genérico), para um ponteiro para o tipo inteiro e usamos o valor nesse ponteiro como nossos dados.

### Exercício 5: Passando Estruturas

**Decisões de Design**:
- Por que alocação dinâmica: Podemos definir o tamanho em tempo de execução, e não temos que nos preocupar com o tamanho da stack podendo fazer estruturas maiores.
- Momento de liberação de memória: Após o thread_join, logo após todas threads terminarem para assim não liberarmos dados usados por nenhuma thread rodando.
- Alternativas consideradas: Podemos usar um array estático já que ja sabemos o número de threads que vão ser criadas, e caso o numero de threads a ser utilizado não seja tão alto.

### Exercício 6: Valores de Retorno

**Análise de Memória**:
- Necessidade de alocação no heap: Obtemos o valor de retorno por meio do endereço de memória dele, se ele existisse na stack, assim que a função em que ele esta acabasse ele poderia ser sobescrito. 
- Problemas com variáveis locais: O comportamento iria ser indefinido, assim que a função acabasse a memoria dessa variavel poderia ser sobescrita e teriamos como retorno valores aleatorios.
- Gerenciamento de memória: Ele permite que a thread principal acessa dados criados pela thread filha, nesse caso ela adciona o valor retornado pela função no segundo paramatro.

## Parte 3: Análise e Reflexões

### Questões Respondidas

1. **Por que pthread_join é necessário?**
   
Para sincronizar execução - garante que a thread principal espere as filhas terminarem antes de continuar. Sem ele, main pode terminar antes das threads, finalizando o programa prematuramente.

2. **Qual a diferença entre passar valores e ponteiros para threads?**
   
Valores: cada thread recebe cópia independente. Ponteiros: threads acessam dados compartilhados na mesma localização de memória, permitindo comunicação mas exigindo sincronização.

3. **O que as threads compartilham e o que é privativo?**
   

Compartilham: heap, variáveis globais, código. Privativo: stack, registradores, variáveis locais.

4. **Por que a ordem de execução das threads é não-determinística?**
   
O scheduler do SO decide quando cada thread executa baseado em prioridades, carga do sistema e outros fatores.

5. **Por que devemos alocar no heap para retornar valores de threads?**
   
Stack da thread é destruída quando ela termina. Heap persiste até free(), permitindo que thread principal acesse o resultado via pthread_join.

6. **Quando vale a pena usar threads em vez de processos?**

Threads: menor overhead, memória compartilhada, comunicação mais rápida. Processos: isolamento total, maior segurança, falha não afeta outros processos.

### Principais Aprendizados

1. A importancia de fazer sincronização das threads para não termos problemas, como condições de corrida.
2. As threads compartilham heap, variaveis globais entre elas, mas não compartilham ponteiros.

### Dificuldades Encontradas

1. **Nesse laboratorio não tive grandes problemas, consegui resolver todos rapidamente**
   
### Possíveis Melhorias

- Achei o material bem intuitivo de se fazer so com as instruções presentes nele.


## Conclusão

[Parágrafo resumindo sua experiência com o laboratório, principais insights sobre programação paralela com threads, e como esse conhecimento pode ser aplicado em projetos futuros]

## Anexos

### Comandos de Compilação Utilizados
```bash
# Liste os comandos exatos que usou
```

### Ambiente de Testes
```bash
# Output de comandos como:
uname -a
gcc --version
nproc
```

---
