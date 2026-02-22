# Relatório: Mini-Projeto 1 - Quebra-Senhas Paralelo

**Aluno(s):** João Vitor de Araújo Trindade (10403255)
---

## 1. Estratégia de Paralelização


**Como você dividiu o espaço de busca entre os workers?**

[Explique seu algoritmo de divisão]

**Código relevante:** Cole aqui a parte do coordinator.c onde você calcula a divisão:
```c
long long passwords_per_worker = total_space/num_workers;
long long remaining = total_space%num_workers;
long long first = remaining + passwords_per_worker;
```

---

## 2. Implementação das System Calls

**Descreva como você usou fork(), execl() e wait() no coordinator:**

* fork(): Criação de processos filhos
Usado para criar os works por meio da duplicação do processo atual, cada chamada fork() duplica o processo atual.
Retorna PID 0 no processo filho, PID positivo no pai, ou -1 em caso de erro

* execl(): Substituição da imagem do processo
Usado nos processos filhos para executar o programa ./worker
Ele passa argumentos para o programa worker.c para assim conseguirmos utiliza-las no processo filho.

* wait(): Para sincronizar os processos para que assim o processo pai consiga 


**Código do fork/exec:**
```c
    for (int i = 0; i < num_workers; i++) {


        pid_t pid = fork(); // TODO 4: Usar fork() para criar processo filho
        long long start_index, end_index; // TODO 5: No processo pai: armazenar PID

        if (i == 0) {
            start_index = 0;
            end_index = remaining + passwords_per_worker - 1;
        }
        else {
            start_index = remaining + (i * passwords_per_worker);
            end_index = start_index + passwords_per_worker - 1;
        }

        // Converter índices para senhas
        char start[password_len + 1];
        char end[password_len + 1];

        if(pid < 0){
            perror("Erro ao iniciar worker!!");
            exit(1);
        }
        else if(pid == 0){
            char start[password_len+1];
            index_to_password(start_index, charset, charset_len, password_len, start);
            char end[password_len+1];
            index_to_password(end_index, charset, charset_len, password_len, end);

            char len_str[16], id_str[16];
            sprintf(len_str, "%d", password_len);
            sprintf(id_str, "%d", i);

            execl("./worker",
                  "worker",
                  target_hash,
                  start,
                  end,
                  charset,
                  len_str,
                  id_str,
                  NULL);

            perror("Erro ao executar worker");
            exit(1);
        }
        else{
            printf("Processo filho criado!! pid: %d \n", pid);
            workers[i] = pid;
        }
    }
```

---

## 3. Comunicação Entre Processos

**Como você garantiu que apenas um worker escrevesse o resultado?**
A escrita foi implementada de forma em que a cada um intervalo arbitrário de tempo verificamos se foi criado o arquivo resultado, caso tenho sido o worker para pois o resultado já foi encontrado, caso contrario ele continua até achar a senha e criar o arquivo contendo essa senha. Isso evita a condição de corrida, pois caso ja criado um arquivo com a resposta outros workers não conseguem acessar por conta da flag O_EXCL.
[Explique como você implementou uma escrita atômica e como isso evita condições de corrida]
Leia sobre condições de corrida (aqui)[https://pt.stackoverflow.com/questions/159342/o-que-%C3%A9-uma-condi%C3%A7%C3%A3o-de-corrida]

**Como o coordinator consegue ler o resultado?**
O coordinator lê o arquvio de resultado por meio da syscall open e read, com elas conseguimos abrir o arquivo onde está o resultado, e move-lo para um buffer local, onde fazemos o parse dos dados, para serem adaptados de forma em que o programa consegui utilizá-los.

---

## 4. Análise de Performance
Complete a tabela com tempos reais de execução:
O speedup é o tempo do teste com 1 worker dividido pelo tempo com 4 workers.

| Teste | 1 Worker | 2 Workers | 4 Workers | Speedup (4w) |
|-------|----------|-----------|-----------|--------------|
| Hash: 202cb962ac59075b964b07152d234b70<br>Charset: "0123456789"<br>Tamanho: 3<br>Senha: "123" | 0.0000s | 0.0000s | 0.0000s | 0 |
| Hash: 5d41402abc4b2a76b9719d911017c592<br>Charset: "abcdefghijklmnopqrstuvwxyz"<br>Tamanho: 5<br>Senha: "hello" | 3.0000s | 3.0000s | 1.0000s | 3 |

**O speedup foi linear? Por quê?**
No caso do primeiro teste, por ser muito simples todas rodam tão rapidos que não é possível de se quantificar a diferença de tempo entre 1 processo só ou multiplos, os teste devem ter diferença de tempo, mas em milisegundos apenas. 

Já no segundo teste podemos ver que temos uma diminuição do tempo entre 1 worker e 4 worker, mas esse speedup não acontece de forma linear. O motivo de ser assim se dá pelo fato de que temos um overhead toda vez que um fork é chamado, já que este é um syscall. Outro motivo, pode ser pelo fato da função time arredondar os tempos, o que faz com que percamos precisão.

---

## 5. Desafios e Aprendizados
**Qual foi o maior desafio técnico que você enfrentou?**
O maior desafio técnico que encontrei foi na hora de lidar com o intervalo de senhas que deveria ser passado aos workers, já que demorei pra entender como funcionava exatamente o processo de entrar em cada worker e como essas informações seriam passadas. Também tive um pouco de dificuldade com o wait para capturar status de saida.

---

## Comandos de Teste Utilizados

```bash
# Teste básico
./coordinator "900150983cd24fb0d6963f7d28e17f72" 3 "abc" 2

# Teste de performance
time ./coordinator "202cb962ac59075b964b07152d234b70" 3 "0123456789" 1
time ./coordinator "202cb962ac59075b964b07152d234b70" 3 "0123456789" 4

# Teste com senha maior
time ./coordinator "5d41402abc4b2a76b9719d911017c592" 5 "abcdefghijklmnopqrstuvwxyz" 4
```
---

**Checklist de Entrega:**
- [x] Código compila sem erros
- [x] Todos os TODOs foram implementados
- [x] Testes passam no `./tests/simple_test.sh`
- [x] Relatório preenchido
