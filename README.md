# Mortgage Software Design, GitHub Workflow, and Google Test

Projeto de desenvolvimento e teste de uma aplicação de cálculo de mortgage em C++, com foco em Reliable Software Engineering.

A solução deve integrar análise de requisitos, arquitetura modular, implementação, testes com Google Test, colaboração no GitHub e integração contínua.

## 1. Objetivo

Desenvolver uma aplicação confiável que calcule o valor de mortgage com base em gênero, idade e salário.

O projeto deve demonstrar:

- Correção da implementação.
- Validação explícita das entradas.
- Cobertura de valores-limite.
- Tratamento de entradas inválidas.
- Separação de responsabilidades.
- Rastreabilidade entre requisitos, implementação e testes.
- Colaboração por branches e pull requests.
- Build e testes automatizados.

## 2. Entregáveis

1. Especificação de requisitos.
2. Arquitetura de software e UML ou fluxograma.
3. Implementação em C++.
4. Suíte de testes com Google Test.
5. Repositório GitHub com branches e pull requests.
6. Workflow de CI e relatório de testes.
7. Relatório técnico final e demonstração.

## 3. Escopo funcional

A aplicação deve receber:

- Gênero.
- Idade.
- Salário.

Após validar as entradas, deve selecionar o fator correspondente e calcular:

```text
mortgage = salary × factor
```

O salário é utilizado diretamente na fórmula. A periodicidade e a moeda precisam ser definidas na especificação de requisitos.

Não fazem parte deste escopo:

- Cálculo de parcela mensal.
- Juros e amortização.
- Cálculo de DTI.
- Consulta a bureau de crédito.
- Aprovação de financiamento real.

## 4. Regras de entrada

| Campo | Restrição |
|---|---|
| Gênero | Male ou Female |
| Idade | Inteiro entre 18 e 55, inclusive |
| Salário | Valor entre 0 e 10.000, inclusive |

As restrições gerais não garantem que exista um fator para toda combinação válida de gênero e idade. Essa situação deve ser tratada explicitamente.

### Tabela de fatores — Male

| Idade | Fator |
|---|---:|
| 18–35 | 75 |
| 36–45 | 55 |
| 46–55 | 30 |

### Tabela de fatores — Female

| Idade | Fator |
|---|---:|
| 18–30 | 70 |
| 31–40 | 50 |
| 41–50 | 35 |

### Lacuna a resolver

A tabela não define fator para Female entre 51 e 55 anos, embora essas idades estejam dentro da restrição geral.

Política proposta, sujeita à aprovação dos requisitos:

- Rejeitar a combinação com erro explícito de fator não definido.
- Não reutilizar automaticamente o fator de outra faixa.
- Não retornar zero silenciosamente.
- Registrar a decisão na especificação e nos testes.

A codificação numérica de gênero, caso utilizada na API, também deve ser documentada.

## 5. Exemplos

| Gênero | Idade | Salário | Fator | Mortgage |
|---|---:|---:|---:|---:|
| Male | 18 | 5.000 | 75 | 375.000 |
| Male | 40 | 5.000 | 55 | 275.000 |
| Female | 30 | 5.000 | 70 | 350.000 |
| Female | 45 | 5.000 | 35 | 175.000 |

## 6. Arquitetura

Fluxo proposto:

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

### Responsabilidades

| Componente | Responsabilidade |
|---|---|
| User/Input Layer | Receber entradas e apresentar resultado ou erro |
| Mortgage Validator | Validar gênero, idade e salário |
| Factor Selector | Selecionar o fator de acordo com a tabela |
| Mortgage Calculator | Multiplicar salário pelo fator |
| Result | Representar ou apresentar a saída |

### Interface sugerida

```cpp
bool validateInputs(int gender, int age, double salary);

double selectFactor(int gender, int age);

double calculateMortgage(double salary, double factor);

double mortgage(int gender, int age, double salary);
```

A função `mortgage` deve coordenar validação, seleção do fator e cálculo.

As exceções e seus significados devem ser documentados antes da implementação. A ausência de fator deve ser distinguida de uma entrada fora do intervalo permitido.

## 7. Estrutura proposta do repositório

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

Essa estrutura é uma proposta de organização, não uma declaração de que todos os arquivos já foram implementados.

## 8. Tecnologias previstas

- C++.
- Google Test.
- CMake.
- Git e GitHub.
- GitHub Actions.

O padrão de C++ e as versões das ferramentas devem ser definidos no projeto e mantidos consistentes entre desenvolvimento e CI.

## 9. Build e execução dos testes

Os comandos abaixo pressupõem que o `CMakeLists.txt` esteja configurado para compilar a aplicação, disponibilizar Google Test e registrar os testes no CTest.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

A forma de obtenção do Google Test deve ser documentada no projeto.

Não apresentar resultados de testes como comprovados antes de executar a suíte e preservar suas evidências.

## 10. Estratégia de testes

### 10.1 Particionamento de equivalência

Cobrir:

- Cada faixa de idade da tabela Male.
- Cada faixa de idade da tabela Female.
- Gênero não reconhecido.
- Idade fora do intervalo.
- Salário fora do intervalo.
- Combinação sem fator definido.

### 10.2 Análise de valores-limite

| Categoria | Valores sugeridos |
|---|---|
| Limite geral de idade | 17, 18, 55, 56 |
| Transições Male | 35, 36, 45, 46 |
| Transições Female | 30, 31, 40, 41, 50, 51 |
| Salário | -1, 0, 1, 9.999, 10.000, 10.001 |

Para salário com casas decimais, adicionar valores imediatamente abaixo e acima dos limites conforme a precisão adotada.

### 10.3 Robustez

Verificar que:

- Entradas inválidas não produzam um resultado aparentemente válido.
- Erros sejam explícitos e consistentes.
- A seleção de fatores respeite os extremos inclusivos.
- A combinação Female, 51–55 siga a política aprovada.
- A lógica de cálculo não esteja duplicada na interface.

### 10.4 Exemplo de teste

O exemplo abaixo pressupõe a definição de `Gender::Male` na interface do projeto.

```cpp
#include <gtest/gtest.h>
#include "mortgage.hpp"

TEST(MortgageTest, MaleLowerAgeBoundary) {
    EXPECT_DOUBLE_EQ(
        mortgage(static_cast<int>(Gender::Male), 18, 5000.0),
        375000.0
    );
}
```

O exemplo é ilustrativo e deve ser adaptado à API efetivamente implementada.

## 11. Workflow no GitHub

### Branches propostas

- `main`: versão estável.
- `develop`: integração.
- `feature/*`: implementação de funcionalidades.
- `test/*`: criação e manutenção dos testes.

### Processo de contribuição

1. Criar uma issue com requisito ou defeito.
2. Criar uma branch relacionada.
3. Implementar a alteração e seus testes.
4. Fazer commits descritivos.
5. Abrir um pull request.
6. Aguardar execução da CI.
7. Realizar revisão de código.
8. Corrigir problemas encontrados.
9. Fazer merge após aprovação.

## 12. Integração contínua

O workflow em `.github/workflows/ci.yml` deve:

1. Executar em push e pull request.
2. Preparar o ambiente de build.
3. Configurar o projeto com CMake.
4. Compilar o código.
5. Executar a suíte Google Test.
6. Disponibilizar o relatório de testes.
7. Sinalizar falha quando build ou testes falharem.

Fluxo esperado:

```text
Push / Pull Request
        ↓
CMake Configure
        ↓
Build
        ↓
Google Test / CTest
        ↓
Test Report
        ↓
Review and Merge ou Correção
```

## 13. Rastreabilidade

Cada requisito deve estar relacionado a um elemento de design, uma função, um teste e uma evidência.

```text
Requirement
    → Design Element
    → Code Function
    → Google Test Case
    → CI Result
    → Evidence
```

### Matriz inicial proposta

| ID | Requisito | Função | Teste previsto |
|---|---|---|---|
| REQ-01 | Validar gênero | `validateInputs` | Gênero não reconhecido |
| REQ-02 | Validar idade entre 18 e 55 | `validateInputs` | 17, 18, 55 e 56 |
| REQ-03 | Validar salário entre 0 e 10.000 | `validateInputs` | Limites e valores externos |
| REQ-04 | Selecionar fator Male | `selectFactor` | Todas as faixas e transições |
| REQ-05 | Selecionar fator Female | `selectFactor` | Todas as faixas e transições |
| REQ-06 | Calcular salário × fator | `calculateMortgage` | Resultados conhecidos |
| REQ-07 | Tratar fator não definido | `selectFactor` | Female entre 51 e 55 |

Os nomes finais dos testes, links de CI e evidências devem ser adicionados após a implementação.

## 14. Critérios de aceite

- [ ] Requisitos documentados e identificados.
- [ ] Política para combinações sem fator aprovada.
- [ ] Codificação de gênero documentada.
- [ ] Arquitetura e UML ou fluxograma disponíveis.
- [ ] Implementação C++ concluída.
- [ ] Testes cobrem todas as faixas de fatores.
- [ ] Limites de idade e salário cobertos.
- [ ] Entradas inválidas tratadas explicitamente.
- [ ] Build e testes passam na CI.
- [ ] Resultados e evidências preservados.
- [ ] Pull requests revisados.
- [ ] Matriz de rastreabilidade preenchida.
- [ ] Relatório técnico final concluído.
- [ ] Release identificada por tag.

## 15. Relatório técnico

O relatório deve incluir:

1. Objetivo e escopo.
2. Requisitos e decisões sobre ambiguidades.
3. Arquitetura e diagramas.
4. Descrição da implementação.
5. Estratégia e casos de teste.
6. Resultados reais da execução.
7. Evidências da CI.
8. Workflow de colaboração.
9. Matriz de rastreabilidade.
10. Limitações e melhorias futuras.

