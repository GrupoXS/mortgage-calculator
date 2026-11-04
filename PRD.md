# PRD — Mortgage Software Design, GitHub Workflow, and Google Test

## 1. Identificação

| Campo | Definição |
|---|---|
| Projeto | Mortgage Software Design, GitHub Workflow, and Google Test |
| Objetivo principal | Reliable Software Engineering |
| Versão do PRD | 2.0 |
| Status | Proposta para implementação e validação |
| Linguagem | C++ |
| Framework de testes | Google Test |
| Build | CMake |
| Repositório e colaboração | GitHub |
| Integração contínua | GitHub Actions |
| Entrega principal | Tested Mortgage Application + Repository + Technical Report |

## 2. Visão do produto

Desenvolver uma aplicação em C++ que calcule o valor de mortgage a partir de gênero, idade e salário, conforme uma tabela de fatores.

Além do resultado funcional, o projeto deve demonstrar um processo de engenharia confiável: requisitos verificáveis, arquitetura modular, testes automatizados, revisão de código, integração contínua e evidências rastreáveis.

O produto é uma aplicação de exercício com regras próprias. Não representa uma política real de concessão de crédito.

## 3. Problema

Uma implementação pode produzir resultados incorretos quando:

- As faixas de idade são interpretadas de forma inconsistente.
- Os limites inclusivos não são testados.
- Entradas inválidas são aceitas silenciosamente.
- Combinações sem fator recebem um valor arbitrário.
- A lógica é duplicada em diferentes partes do código.
- Alterações são integradas sem revisão ou testes.
- Não existem evidências que relacionem requisitos e resultados.

O projeto deve reduzir esses riscos por meio de design explícito, validação e verificação automatizada.

## 4. Objetivos

### 4.1 Objetivos funcionais

- Receber gênero, idade e salário.
- Validar as entradas.
- Identificar o fator aplicável.
- Calcular `mortgage = salary × factor`.
- Apresentar o resultado ou um erro explícito.

### 4.2 Objetivos de engenharia

- Separar entrada, validação, seleção de fator e cálculo.
- Cobrir faixas válidas, transições e entradas inválidas.
- Automatizar build e testes.
- Manter rastreabilidade dos requisitos.
- Registrar colaboração por issues, commits e pull requests.
- Entregar relatório técnico com resultados reais.

## 5. Usuários e stakeholders

| Perfil | Necessidade |
|---|---|
| Usuário da aplicação | Informar dados e receber resultado ou erro compreensível |
| Desenvolvedor | Implementar e manter regras sem duplicação |
| Responsável por testes | Verificar cálculos, limites e falhas |
| Revisor | Conferir aderência aos requisitos e qualidade do código |
| Avaliador do projeto | Consultar execução, evidências e rastreabilidade |

## 6. Escopo

### 6.1 Dentro do escopo

- Aplicação C++ com interface de linha de comando proposta para o MVP.
- Validação de gênero, idade e salário.
- Seleção de fatores por gênero e faixa etária.
- Cálculo do valor de mortgage.
- Tratamento explícito de erros.
- Testes com Google Test.
- Build com CMake.
- Execução de testes por CTest.
- Repositório GitHub.
- Workflow com branches e pull requests.
- CI com GitHub Actions.
- Documentação e relatório técnico.

### 6.2 Fora do escopo

- Cálculo de parcelas, juros e amortização.
- DTI e análise de capacidade de pagamento.
- Aprovação de financiamento real.
- Integração com instituições financeiras.
- Consulta a bureau de crédito.
- Gestão documental.
- Persistência em banco de dados.
- API REST.
- Interface web ou aplicativo móvel.
- Conformidade regulatória de um produto financeiro real.

## 7. Regras de negócio

### RN-01 — Fórmula

```text
mortgage = salary × factor
```

### RN-02 — Gênero

Os valores de domínio definidos no enunciado são:

- Male.
- Female.

Qualquer outro valor deve ser rejeitado.

Se a implementação utilizar códigos numéricos, o mapeamento deve ser documentado e compartilhado entre código, interface e testes.

### RN-03 — Idade

A idade deve ser um número inteiro entre 18 e 55, inclusive.

### RN-04 — Salário

O salário deve ser um número finito entre 0 e 10.000, inclusive.

A moeda e a periodicidade não foram definidas no enunciado. O cálculo deve usar o valor informado diretamente, sem conversão presumida.

### RN-05 — Fatores Male

| Idade | Fator |
|---|---:|
| 18–35 | 75 |
| 36–45 | 55 |
| 46–55 | 30 |

### RN-06 — Fatores Female

| Idade | Fator |
|---|---:|
| 18–30 | 70 |
| 31–40 | 50 |
| 41–50 | 35 |

### RN-07 — Combinações sem fator

O enunciado não define fator para Female entre 51 e 55 anos.

Política proposta para aprovação:

- Considerar a idade dentro do intervalo geral.
- Identificar a combinação como sem fator definido.
- Retornar erro explícito.
- Não aplicar fator de outra faixa.
- Não retornar zero como substituição do erro.

Essa política deve ser aprovada e registrada antes do aceite final.

### RN-08 — Salário zero

Salário zero é uma entrada permitida.

Quando houver fator definido, o resultado deve ser zero.

Salário zero não elimina a necessidade de validar gênero, idade e existência de fator.

## 8. Fluxo principal

1. O usuário informa gênero, idade e salário.
2. A interface verifica se os dados podem ser interpretados.
3. O validador verifica o domínio das entradas.
4. O seletor identifica o fator.
5. O calculador multiplica salário pelo fator.
6. A aplicação apresenta o resultado.

### Fluxo de erro

1. Uma entrada inválida ou combinação sem fator é identificada.
2. A aplicação interrompe o cálculo.
3. A aplicação apresenta uma mensagem compreensível.
4. Nenhum valor de mortgage é apresentado como resultado válido.

## 9. Requisitos funcionais

### RF-01 — Receber entradas

A aplicação deve receber gênero, idade e salário.

Critérios de aceite:

- Os três campos são obrigatórios.
- Texto não numérico em idade ou salário é rejeitado.
- Idade fracionária não é truncada silenciosamente.

### RF-02 — Validar gênero

A aplicação deve aceitar apenas os valores de gênero documentados.

Critérios de aceite:

- Male e Female seguem para as demais validações.
- Valores não reconhecidos geram erro explícito.

### RF-03 — Validar idade

A aplicação deve aceitar idades inteiras de 18 a 55.

Critérios de aceite:

- 18 e 55 passam pela validação geral de idade.
- 17 e 56 são rejeitados.
- A existência de fator é verificada separadamente.

### RF-04 — Validar salário

A aplicação deve aceitar salários finitos de 0 a 10.000.

Critérios de aceite:

- 0 e 10.000 são aceitos.
- Valores negativos e acima de 10.000 são rejeitados.
- NaN e infinito são rejeitados na camada de domínio.

### RF-05 — Selecionar fator

A aplicação deve selecionar exatamente o fator previsto na tabela.

Critérios de aceite:

- Todas as faixas usam extremos inclusivos.
- As transições entre faixas não possuem sobreposição.
- Combinações sem fator seguem a política aprovada.

### RF-06 — Calcular mortgage

A aplicação deve multiplicar salário pelo fator selecionado.

Critérios de aceite:

- Male, 18 anos, salário 5.000 resulta em 375.000.
- Male, 40 anos, salário 5.000 resulta em 275.000.
- Female, 30 anos, salário 5.000 resulta em 350.000.
- Female, 45 anos, salário 5.000 resulta em 175.000.

### RF-07 — Apresentar resultado ou erro

A aplicação deve distinguir sucesso de falha.

Critérios de aceite:

- Em sucesso, apresenta o valor calculado.
- Em falha, apresenta a causa.
- Na interface de linha de comando proposta, sucesso retorna código zero e erro retorna código diferente de zero.

### RF-08 — Executar testes automatizados

O projeto deve incluir uma suíte Google Test registrada no CTest.

Critérios de aceite:

- A suíte executa sem interação manual.
- Falhas de teste tornam a execução malsucedida.
- O relatório permite identificar os casos que falharam.

### RF-09 — Automatizar build e testes

O repositório deve executar build e testes por GitHub Actions.

Critérios de aceite:

- O workflow executa em push e pull request.
- Falhas de configuração, compilação ou teste sinalizam falha.
- Evidências de teste ficam associadas à execução.

## 10. Requisitos não funcionais

| ID | Categoria | Requisito verificável |
|---|---|---|
| RNF-01 | Correção | Todos os cenários de aceite devem passar |
| RNF-02 | Determinismo | Mesmas entradas devem gerar o mesmo resultado ou erro |
| RNF-03 | Modularidade | Entrada, validação, seleção e cálculo devem ter responsabilidades separadas |
| RNF-04 | Manutenibilidade | As tabelas de fatores não devem ser duplicadas na interface |
| RNF-05 | Robustez | Entradas inválidas não devem gerar sucesso silencioso |
| RNF-06 | Reprodutibilidade | Build e testes devem executar com os comandos documentados |
| RNF-07 | Rastreabilidade | Cada requisito funcional deve estar ligado a testes e evidências |
| RNF-08 | Colaboração | Alterações entregues devem possuir histórico de revisão por pull request |
| RNF-09 | Documentação | Instruções e decisões devem corresponder ao código entregue |

## 11. Arquitetura proposta

```text
User/Input Layer
        ↓
Mortgage Validator
        ↓
Factor Selector
        ↓
Mortgage Calculator
        ↓
Result
```

### Componentes

| Componente | Responsabilidade |
|---|---|
| Input Layer | Interpretar entradas e apresentar saídas |
| Mortgage Validator | Verificar restrições do domínio |
| Factor Selector | Aplicar a tabela de fatores |
| Mortgage Calculator | Executar a multiplicação |
| Result/Error Handling | Representar sucesso ou falha |

### Interfaces de referência

```cpp
bool validateInputs(int gender, int age, double salary);

double selectFactor(int gender, int age);

double calculateMortgage(double salary, double factor);

double mortgage(int gender, int age, double salary);
```

Essas assinaturas são uma referência de design, não evidência de implementação.

A função `mortgage` deve coordenar as etapas sem duplicar as regras.

A estratégia de erros deve ser documentada. Deve distinguir, no mínimo:

- Entrada inválida.
- Combinação sem fator definido.

## 12. Estrutura proposta do repositório

```text
mortgage-application/
├── .github/
│   └── workflows/
│       └── ci.yml
├── include/
│   └── mortgage.hpp
├── src/
│   ├── mortgage.cpp
│   └── main.cpp
├── tests/
│   └── mortgage_test.cpp
├── docs/
│   ├── requirements.md
│   ├── architecture.md
│   ├── traceability-matrix.md
│   └── technical-report.md
├── CMakeLists.txt
└── README.md
```

## 13. Estratégia de testes

### 13.1 Particionamento de equivalência

A suíte deve cobrir:

- As três faixas Male.
- As três faixas Female com fator definido.
- Gênero inválido.
- Idade abaixo e acima do intervalo.
- Salário abaixo e acima do intervalo.
- Combinação Female sem fator definido.

### 13.2 Valores-limite

| Grupo | Valores obrigatórios |
|---|---|
| Intervalo geral de idade | 17, 18, 55, 56 |
| Transições Male | 35, 36, 45, 46 |
| Transições Female | 30, 31, 40, 41, 50, 51 |
| Salário | -1, 0, 1, 9.999, 10.000, 10.001 |

Os testes devem verificar os resultados esperados, não apenas executar as entradas.

### 13.3 Robustez

Adicionar cenários para:

- Gênero não reconhecido.
- Idade ou salário não numérico na interface.
- Idade fracionária na interface.
- Salário NaN ou infinito na camada de domínio.
- Mais de uma entrada inválida.
- Salário zero com combinação sem fator.

### 13.4 Tabela de decisão

| Entrada válida? | Fator definido? | Resultado |
|---|---|---|
| Não | Não aplicável | Erro de validação |
| Sim | Não | Erro de fator não definido |
| Sim | Sim | Salário × fator |

### 13.5 Níveis de teste

- Unitários: validação, seleção de fator e cálculo.
- Integração: função coordenadora `mortgage`.
- Interface: interpretação das entradas e apresentação de erros.
- CI: configuração, compilação e execução automatizada da suíte.

## 14. Build e integração contínua

### Comandos de referência

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Esses comandos pressupõem um `CMakeLists.txt` configurado com os alvos e testes necessários.

### Pipeline esperado

```text
Push / Pull Request
        ↓
Preparar ambiente
        ↓
Configurar CMake
        ↓
Compilar
        ↓
Executar testes
        ↓
Publicar evidências
        ↓
Revisar e integrar ou corrigir
```

O padrão de C++, as versões das ferramentas e a obtenção do Google Test devem ser definidos e documentados.

## 15. Workflow de colaboração

### Branches propostas

| Branch | Finalidade |
|---|---|
| `main` | Versão estável |
| `develop` | Integração |
| `feature/*` | Funcionalidades |
| `test/*` | Testes e verificações |

### Processo

1. Registrar issue ou requisito.
2. Criar branch relacionada.
3. Implementar código e testes.
4. Registrar commits descritivos.
5. Abrir pull request.
6. Executar CI.
7. Revisar implementação, testes e documentação.
8. Corrigir problemas.
9. Integrar após aprovação.

## 16. Rastreabilidade

Fluxo obrigatório:

```text
Requirement
    → Design Element
    → Code Function
    → Google Test Case
    → CI Result
    → Evidence
```

### Matriz inicial

| Requisito | Componente | Evidência esperada |
|---|---|---|
| RF-01 | Input Layer | Testes de interpretação |
| RF-02 | Validator | Testes de gênero |
| RF-03 | Validator | Testes de idade |
| RF-04 | Validator | Testes de salário |
| RF-05 | Factor Selector | Testes de faixas e transições |
| RF-06 | Calculator | Testes de resultados conhecidos |
| RF-07 | Result/Input Layer | Testes de saída e erro |
| RF-08 | Test Suite | Relatório Google Test/CTest |
| RF-09 | CI Workflow | Execução GitHub Actions |

A matriz final deve incluir nomes reais dos testes, referência ao commit e localização das evidências.

## 17. Entregáveis e critérios de aceite

| Entregável | Conteúdo mínimo | Critério de aceite |
|---|---|---|
| Requisitos | Regras, restrições, IDs e decisões | Sem ambiguidades bloqueadoras |
| Design | Arquitetura, interfaces e UML/fluxograma | Coerente com a implementação |
| Aplicação | Código C++ e interface proposta | Build concluído e cenários corretos |
| Testes | Suíte Google Test | Casos obrigatórios aprovados |
| Repositório | Código, branches, commits e PRs | Histórico e revisões consultáveis |
| CI | Workflow e relatórios | Execução aprovada para a versão entregue |
| Relatório técnico | Métodos, resultados, evidências e limitações | Resultados vinculados à versão entregue |

## 18. Métricas de qualidade

| Métrica | Meta de aceite |
|---|---|
| Requisitos funcionais com testes associados | 100% |
| Faixas de fatores verificadas | 100% |
| Transições de idade previstas verificadas | 100% |
| Cenários obrigatórios aprovados | 100% |
| Defeitos bloqueadores conhecidos | 0 |
| CI da versão entregue | Aprovada |
| Alterações entregues revisadas por PR | 100% |

Cobertura de código, caso medida, deve ser relatada separadamente. Ela não substitui a verificação dos requisitos.

## 19. Riscos e mitigação

| Risco | Mitigação |
|---|---|
| Ausência de fator para Female 51–55 | Aprovar e testar política explícita |
| Erros nos extremos das faixas | Testes de valores-limite |
| Mapeamento de gênero inconsistente | Definição única e documentada |
| Aceitação de salário inválido | Validação de intervalo e finitude |
| Divergência entre ambiente local e CI | Ferramentas e comandos documentados |
| Regras duplicadas | Revisão de design e código |
| Alegações de teste sem evidência | Preservar relatórios vinculados ao commit |

## 20. Marcos de entrega

### Marco 1 — Requisitos

- Regras identificadas.
- Ambiguidades resolvidas.
- Critérios de aceite aprovados.

### Marco 2 — Design

- Arquitetura definida.
- Interfaces e erros documentados.
- UML ou fluxograma disponível.

### Marco 3 — Implementação

- Componentes C++ implementados.
- Build local configurado.
- Interface funcional.

### Marco 4 — Verificação

- Suíte Google Test implementada.
- Limites e cenários negativos cobertos.
- Falhas corrigidas.

### Marco 5 — Integração e entrega

- CI aprovada.
- Pull requests revisados.
- Matriz de rastreabilidade preenchida.
- Relatório técnico concluído.
- Release identificada por tag.

## 21. Definition of Done

O projeto será considerado concluído quando:

- [ ] Todos os requisitos obrigatórios estiverem implementados.
- [ ] A política para Female 51–55 estiver aprovada e testada.
- [ ] O código compilar com o ambiente documentado.
- [ ] Todos os testes obrigatórios passarem.
- [ ] Não houver defeitos bloqueadores conhecidos.
- [ ] A CI da versão entregue estiver aprovada.
- [ ] As revisões por pull request estiverem registradas.
- [ ] A matriz de rastreabilidade estiver completa.
- [ ] README, arquitetura e relatório estiverem atualizados.
- [ ] As evidências corresponderem ao commit da entrega.
- [ ] A versão final estiver identificada por tag.

