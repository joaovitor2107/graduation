# 📝 Relatório do Laboratório 2 - Chamadas de Sistema

---

## 1️⃣ Exercício 1a - Observação printf() vs 1b - write()

### 💻 Comandos executados:
```bash
strace -e write ./ex1a_printf
strace -e write ./ex1b_write
```

### 🔍 Análise

**1. Quantas syscalls write() cada programa gerou?**
- ex1a_printf: 9 syscalls
- ex1b_write: 7 syscalls

**2. Por que há diferença entre os dois métodos? Consulte o docs/printf_vs_write.md**

```
Essa diferença entre os dois métodos se dá pelo fato de que cada vez que o printf é chamado você não tem necessariamente uma chamada de syscall, você pode ter vários printf e uma só chamada e um só printf e mais de uma chamada de write. Nesse caso em específico temos que em cada uma das linhas de printf que contem dois \n, nós temos dois syscall e aqui temos duas assim, sendo o motivo da diferença do número de syscall de write.
```

**3. Qual método é mais previsível? Por quê você acha isso?**

```
O método mais previsível é o write(), apesar de ser mais lento na maioria dos casos aqui sabemos exatamente quantas syscalls serão feitas dado que cada chamada de write é uma syscall.
```

---

## 2️⃣ Exercício 2 - Leitura de Arquivo

### 📊 Resultados da execução:
- File descriptor: 3
- Bytes lidos: 127

### 🔧 Comando strace:
```bash
strace -e openat,read,close ./ex2_leitura
```

### 🔍 Análise

**1. Qual file descriptor foi usado? Por que não começou em 0, 1 ou 2?**

```
O file descriptor usado foi o 3, e não utilizamos o 0,1 ou 2 porque esses são reservados para entrada(scanf), saida(printf) e para saida de erro. Então temos o primeiro file descriptor após esse.
```

**2. Como você sabe que o arquivo foi lido completamente?**

```
Nos sabemos que o arquivo foi lido completamente quando o retorno da função read é 0
```

**3. Por que verificar retorno de cada syscall?**

```
Para podermos ter garantias do funcionamento das operações, caso tentemos ler um arquivo que não conseguimos abrir por exemplo poderemos ter erros e bugs inesperados e queremos evitar isso, pois estamos lidando com syscall que são executadas diretamente pelo kernel.
```

---

## 3️⃣ Exercício 3 - Contador com Loop

### 📋 Resultados (BUFFER_SIZE = 64):
- Linhas: 25 (esperado: 25)
- Caracteres: 1300
- Chamadas read(): 21 - mas no strace diz que são 23
- Tempo: 0.000101 segundos

### 🧪 Experimentos com buffer:

| Buffer Size | Syscalls read() | Tempo (s) | Chars/seg |
|-------------|-----------------|-----------|-----------|
| 16          | 83              | 0.000217  |  5990783  |
| 64          | 22              | 0.000130  | 10000000  |
| 256         | 7               | 0.000103  | 12621359  |
| 1024        | 3               | 0.000078  | 16666666  |

### 🔍 Análise

**1. Como o tamanho do buffer afeta o número de syscalls?**

```
Quanto menor o buffer maior o número de syscalls necessárias para conseguir ler o arquivo, dado que cada syscall de read só consegue ler o tamanho do buffer, então se o buffer for menor que o arquivo demora mais. 
```

**2. Todas as chamadas read() retornaram BUFFER_SIZE bytes? Discorra brevemente sobre**

```
Nem todas, quando chegamos em EOF, por exemplo, read() retorna só a quantidade de bytes lidos até o EOF.
```

**3. Qual é a relação entre syscalls e performance?**

```
Quanto mais syscalls são feitos menor a performance do nosso programa dado que a cada syscall temos overhead do sistema (mudança entre o espaço do usuário e o kernel), o que faz com que precisemos guardar registradores, executar a operaçõe e ai voltar para o espaço do usuário.
```

---

## 4️⃣ Exercício 4 - Cópia de Arquivo

### 📈 Resultados:
- Bytes copiados: 1364 
- Operações: 6
- Tempo: 0.000296 segundos
- Throughput: 4500.11 KB/s

### ✅ Verificação:
```bash
diff dados/origem.txt dados/destino.txt
```
Resultado: [X] Idênticos [ ] Diferentes

### 🔍 Análise

**1. Por que devemos verificar que bytes_escritos == bytes_lidos?**

```
Para assim poder verificar que não ocorreu nenhum erro durante a escrita do nosso arquivo.
```

**2. Que flags são essenciais no open() do destino?**

```
São essenciais as flags: 
O_WRONLY - para abrir o arquivo para escrita
O_CREAT - para criar o arquivo caso ele não exista
O_TRUNC - para caso o arquivo já exista com texto, ele seja limpo
```

**3. O número de reads e writes é igual? Por quê?**

```
Não são iguais, porque temos os writes também dos printfs que existem pelo arquivo
```

**4. Como você saberia se o disco ficou cheio?**

```
Poderiamos saber caso nosso arquivo fosse escrito so até certo ponto, e caso na hora de escrever recebessemos como retorno -1 com o erro, No space left on device.
```

**5. O que acontece se esquecer de fechar os arquivos?**

```
Ficariamos com recursos dos sistemas ainda sendo usados mesmo, e limitariamos o número de file descriptors disponiveis.
```

---

## 🎯 Análise Geral

### 📖 Conceitos Fundamentais

**1. Como as syscalls demonstram a transição usuário → kernel?**

```
Cada syscall faz a transição usuário -> kernell -> usuário, pois as ações executadas pelos syscall só podem ser executados no modo kernel.
```

**2. Qual é o seu entendimento sobre a importância dos file descriptors?**

```
Os file descriptors são importantes pois eles servem para controle das operações de kernell, assim conseguimos indentificar qual arquivo abrimos com open e aplicar operações de syscall nele.
```

**3. Discorra sobre a relação entre o tamanho do buffer e performance:**

```
Quanto maior o buffer menos syscall teremos que ter e menos overhead vamos sofrer, em compensação a depender de quão grande o buffer for ele pode não caber mais no cache o que faz com que as operações de acesso sejam mais lentas também.
```

### ⚡ Comparação de Performance

```bash
# Teste seu programa vs cp do sistema
time ./ex4_copia
time cp dados/origem.txt dados/destino_cp.txt
```

**Qual foi mais rápido?** cp - com diferença mínima

**Por que você acha que foi mais rápido?**

```
Acredito que deve ser mais otimizado em relação a tamanho de buffer, e em relação as syscalls.
```

---

## 📤 Entrega
Certifique-se de ter:
- [x] Todos os códigos com TODOs completados
- [x] Traces salvos em `traces/`
- [x] Este relatório preenchido como `RELATORIO.md`

```bash
strace -e write -o traces/ex1a_trace.txt ./ex1a_printf
strace -e write -o traces/ex1b_trace.txt ./ex1b_write
strace -o traces/ex2_trace.txt ./ex2_leitura
strace -c -o traces/ex3_stats.txt ./ex3_contador
strace -o traces/ex4_trace.txt ./ex4_copia
```
# Bom trabalho!
