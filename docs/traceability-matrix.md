# Matriz de rastreabilidade inicial

Esta matriz liga requisitos do PRD aos testes Google Test atualmente implementados. A execução local foi feita diretamente com o compilador porque CMake não está instalado neste ambiente; a configuração CMake/CTest será usada pela CI e após a instalação local do CMake.

| Requisito | Testes associados | Cobertura atual |
|---|---|---|
| RF-02 — Validar gênero | `ValidateInputsTest.RejectsUnknownGender` | Gênero não reconhecido |
| RF-03 — Validar idade | `ValidateInputsTest.AcceptsInclusiveGeneralBounds`, `ValidateInputsTest.RejectsAgeOutsideInclusiveBounds` | Idades inclusivas 18/55 e inválidas 17/56 |
| RF-04 — Validar salário | `ValidateInputsTest.AcceptsInclusiveGeneralBounds`, `ValidateInputsTest.RejectsSalaryOutsideInclusiveBounds`, `ValidateInputsTest.RejectsNonFiniteSalary` | Limites 0/10.000, valores externos, NaN e infinito |
| RF-05 — Selecionar fator | `SelectFactorTest.SelectsExpectedFactorsAtEveryRangeBoundary`, `SelectFactorTest.ReportsNoFactorForFemaleAgesFiftyOneThroughFiftyFive`, `SelectFactorTest.ReturnsNoFactorForInvalidAgeOrGender` | Limites das faixas e combinações sem fator |
| RF-06 — Calcular mortgage | `CalculateMortgageTest.MultipliesSalaryByFactor`, `CalculateTest.ReturnsExpectedResultsForRequirementsExamples` | Multiplicação e quatro exemplos do PRD |
| RF-07 — Retornar sucesso ou erro | `CalculateTest.ReturnsExplicitErrorsInsteadOfAValue`, `CalculateTest.ZeroSalaryDoesNotHideMissingFactor` | Erros tipados e fator ausente mesmo com salário zero |

RF-01 (interpretação da entrada da CLI), RF-08 (execução automatizada) e RF-09 (CI) ainda dependem da implementação da interface e da validação do workflow. Os testes atuais verificam a camada de domínio, não a CLI.

**Decisão pendente:** os testes tratam Female entre 51 e 55 como `FactorNotDefined`, conforme política proposta no PRD. Essa decisão ainda requer aprovação dos requisitos antes do aceite final.