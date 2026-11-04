# Mortgage Application

Aplicação mínima e testável para cálculo e avaliação de empréstimos hipotecários (*mortgage*).

O projeto implementa cálculo de parcela mensal, amortização, DTI e decisão automática de aprovação ou recusa, com foco em engenharia de software confiável.

## Funcionalidades

- Cálculo da parcela mensal.
- Geração da tabela de amortização.
- Cálculo de DTI (*Debt-to-Income*).
- Decisão automática: `approved` ou `declined`.
- Validação de entradas inválidas.
- Testes automatizados.

## Regras de negócio

- A parcela mensal é calculada pela fórmula padrão de amortização.
- Empréstimos com juros zero dividem o principal igualmente pelo número de parcelas.
- O DTI é calculado como obrigações mensais divididas pela renda mensal bruta.
- DTI menor ou igual a 43% resulta em aprovação.
- DTI maior que 43% resulta em recusa.
- Principal e prazo devem ser positivos.
- A taxa anual não pode ser negativa.

## Estrutura do projeto

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

| Arquivo | Responsabilidade |
|---|---|
| `src/mortgage/calculator.py` | Cálculo de parcela e amortização |
| `src/mortgage/application.py` | Avaliação da solicitação e decisão |
| `tests/` | Testes automatizados |
| `docs/technical-report.md` | Relatório técnico |
| `conftest.py` | Configuração do caminho de importação para testes |

## Requisitos

- Python 3.10 ou superior
- pytest

## Instalação

```bash
pip install pytest
```

## Executar os testes

Na raiz do projeto, execute:

```bash
pytest -q
```

Resultado esperado:

```text
7 passed
```

## Exemplo de uso

```python
from mortgage.application import evaluate_application

application = {
    "applicant": "Ana",
    "principal": 200000,
    "annual_rate": 6,
    "years": 30,
    "annual_income": 96000,
    "monthly_debts": 500
}

result = evaluate_application(application)

print(result["monthly_payment"])
print(result["dti"])
print(result["decision"])
```

## Exemplo de resposta

```json
{
  "applicant": "Ana",
  "monthly_payment": 1199.10,
  "dti": 0.2124,
  "decision": "approved"
}
```

## Testes cobertos

- Cálculo de parcela com cenário de referência.
- Empréstimo com juros zero.
- Amortização completa até saldo zero.
- Principal inválido.
- Campos obrigatórios ausentes.
- Solicitação aprovada.
- Solicitação recusada.

## Critérios de aceite

- Todos os testes passam.
- O cálculo de parcela é determinístico.
- A amortização termina com saldo zero.
- Entradas inválidas geram erros claros.
- A decisão segue a regra de DTI documentada.

## Próximos passos

- Adicionar API REST.
- Adicionar persistência em banco de dados.
- Incluir cálculo de LTV.
- Adicionar gestão documental.
- Criar pipeline de CI/CD.