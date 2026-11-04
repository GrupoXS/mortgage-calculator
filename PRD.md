# PRD — Mortgage Software Design and Testing

**Goal:** Reliable Software Engineering

**Deliverables:** Tested Mortgage Application + Repository + Technical Report

## 1. Visão geral

Este projeto entrega uma aplicação de mortgage testável, um repositório organizado e um relatório técnico. O foco é engenharia de software confiável: cálculos financeiros determinísticos, validação de entradas, testes automatizados e documentação clara.

## 2. Objetivos

- Implementar cálculo confiável de parcela mensal e amortização.
- Avaliar solicitações de crédito com base no DTI.
- Garantir que entradas inválidas falhem de forma segura e explícita.
- Criar testes automatizados para cenários normais, limites e falhas.
- Documentar arquitetura, regras de negócio, testes e critérios de aceite.

## 3. Escopo

### Dentro do escopo

- Cálculo de parcela mensal.
- Geração de tabela de amortização.
- Cálculo de DTI.
- Decisão automática de aprovação ou recusa.
- Validação de dados de entrada.
- Testes unitários, de limite e de falha.
- Relatório técnico e estrutura de repositório.

### Fora do escopo inicial

- Gestão documental.
- Integração com bureau de crédito.
- Avaliação de imóveis.
- Persistência em banco de dados.
- API REST pública.
- Relatórios regulatórios.
- Infraestrutura de produção.

## 4. Usuários

| Usuário | Necessidade |
|---|---|
| Solicitante | Calcular condições e entender decisão de crédito |
| Loan officer | Avaliar solicitações de forma consistente |
| Underwriter | Aplicar regras de risco e DTI |
| Engenharia/QA | Executar testes automatizados e manter qualidade |
| Auditoria | Consultar regras, resultados e evidências de teste |

## 5. Regras de negócio

- A parcela mensal é calculada pela fórmula padrão de amortização.
- Empréstimos com juros zero dividem o principal igualmente pelo número de parcelas.
- O DTI é calculado como obrigações mensais divididas pela renda mensal bruta.
- Solicitações com DTI menor ou igual a 43% são aprovadas.
- Solicitações com DTI maior que 43% são recusadas.
- Principal deve ser positivo.
- Prazo deve ser positivo.
- Taxa anual não pode ser negativa.
- Campos obrigatórios ausentes devem gerar erro claro.

## 6. Requisitos funcionais

### RF-01 — Cálculo de parcela

O sistema deve calcular a parcela mensal a partir de principal, taxa anual e prazo em anos.

### RF-02 — Amortização

O sistema deve gerar uma tabela com mês, pagamento, juros, amortização de principal e saldo remanescente.

### RF-03 — Avaliação da solicitação

O sistema deve calcular DTI e retornar uma decisão de `approved` ou `declined`.

### RF-04 — Validação

O sistema deve rejeitar principal inválido, prazo inválido, taxa negativa e campos obrigatórios ausentes.

### RF-05 — Testes automatizados

O sistema deve incluir testes automatizados executáveis por comando único.

## 7. Requisitos não funcionais

| Categoria | Requisito |
|---|---|
| Confiabilidade | Cálculos devem ser determinísticos e reproduzíveis |
| Manutenibilidade | Lógica financeira isolada em funções puras |
| Testabilidade | Testes automatizados para casos normais, limite e falha |
| Segurança | Entradas inválidas não devem causar falhas silenciosas |
| Documentação | README e relatório técnico devem acompanhar o repositório |
| CI/CD readiness | Estrutura preparada para integração contínua |

## 8. Arquitetura

| Camada | Responsabilidade |
|---|---|
| `calculator.py` | Cálculos financeiros puros |
| `application.py` | Avaliação da solicitação e política de decisão |
| `tests/` | Testes automatizados |
| `docs/` | Relatório técnico |
| `README.md` | Instruções de uso e execução |

## 9. Estrutura do repositório

```text
mortgage-application/
├── README.md
├── conftest.py
├── docs/
│   └── technical-report.md
├── src/
│   └── mortgage/
│       ├── calculator.py
│       └── application.py
└── tests/
    ├── test_calculator.py
    └── test_application.py
```

## 10. Estratégia de testes

| Tipo de teste | Cobertura |
|---|---|
| Unitário | Cálculo de parcela e amortização |
| Limite | Juros zero e saldo final igual a zero |
| Falha | Principal inválido e campos ausentes |
| Decisão | Aprovação e recusa por DTI |

### Casos de teste

1. Parcela de US$ 200.000, 6% ao ano e 30 anos deve ser US$ 1.199,10.
2. Empréstimo de US$ 120.000, 0% ao ano e 10 anos deve ter parcela de US$ 1.000,00.
3. Principal igual a zero deve gerar erro.
4. A amortização de US$ 100.000, 5% ao ano e 15 anos deve terminar com saldo zero.
5. Solicitação com DTI dentro do limite deve ser aprovada.
6. Solicitação com DTI acima do limite deve ser recusada.
7. Solicitação sem campos obrigatórios deve gerar erro.

## 11. Critérios de aceite

- Todos os testes automatizados passam.
- O cálculo de parcela corresponde ao cenário de referência.
- A amortização termina com saldo zero.
- Entradas inválidas falham com erro explícito.
- A decisão segue a regra de DTI documentada.
- O repositório contém aplicação, testes, README e relatório técnico.

## 12. Métricas de sucesso

| Métrica | Meta |
|---|---|
| Testes automatizados aprovados | 100% |
| Defeitos críticos em cálculo financeiro | 0 |
| Cobertura de cenários de falha | Implementada |
| Documentação técnica | Completa |
| Reprodutibilidade dos testes | Execução com comando único |

## 13. Riscos e mitigações

| Risco | Mitigação |
|---|---|
| Erro em cálculo financeiro | Testes de referência e casos-limite |
| Entradas inválidas | Validação explícita e testes negativos |
| Regras de crédito incorretas | Regras documentadas e testadas |
| Falta de rastreabilidade | Relatório técnico e critérios de aceite |
| Dívida técnica | Estrutura modular e testes automatizados |

## 14. Resultado da validação

```text
7 passed in 0.01s
```

## 15. Como executar

```bash
cd mortgage-application
pip install pytest
pytest -q
```

## 16. Próximos passos

- Adicionar API REST.
- Adicionar persistência.
- Incluir LTV e avaliação do imóvel.
- Adicionar gestão documental e trilha de auditoria.
- Criar pipeline de CI/CD com cobertura, linting e segurança.