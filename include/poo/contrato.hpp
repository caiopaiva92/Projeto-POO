#ifndef POO_CONTRATO_HPP
#define POO_CONTRATO_HPP

#include "poo/Escrituravel.hpp"
#include "poo/Estoque.hpp"
#include "poo/MedicamentoControlado.hpp"
#include "poo/MedicamentoIsento.hpp"
#include "poo/MedicamentoSobPrescricao.hpp"
#include "poo/Produto.hpp"

#include <memory>
#include <type_traits>
#include <vector>


static_assert(std::is_abstract_v<poo::Produto>,
              "Produto tem de ser abstrata: nao existe produto generico na prateleira");

static_assert(std::has_virtual_destructor_v<poo::Produto>,
              "Produto tem de ter destrutor virtual: o Estoque apaga por ponteiro para Produto");


static_assert(!std::is_copy_constructible_v<poo::Produto>,
              "Produto nao pode ser copiado: copiar a base por valor fatiaria o medicamento");
static_assert(!std::is_copy_assignable_v<poo::Produto>,
              "Produto nao pode ser atribuido por copia");


static_assert(std::is_abstract_v<poo::Escrituravel>,
              "Escrituravel tem de ser abstrata (so funcoes puras)");
static_assert(sizeof(poo::Escrituravel) == sizeof(void*),
              "Escrituravel nao pode ter atributos: seu tamanho e so o do ponteiro virtual");


static_assert(!std::is_abstract_v<poo::MedicamentoIsento> &&
                  std::is_final_v<poo::MedicamentoIsento>,
              "MedicamentoIsento tem de ser concreta e final");
static_assert(!std::is_abstract_v<poo::MedicamentoSobPrescricao> &&
                  std::is_final_v<poo::MedicamentoSobPrescricao>,
              "MedicamentoSobPrescricao tem de ser concreta e final");
static_assert(!std::is_abstract_v<poo::MedicamentoControlado> &&
                  std::is_final_v<poo::MedicamentoControlado>,
              "MedicamentoControlado tem de ser concreta e final");


static_assert(std::is_convertible_v<poo::MedicamentoIsento*, poo::Produto*>,
              "MedicamentoIsento tem de herdar publicamente de Produto");
static_assert(std::is_convertible_v<poo::MedicamentoSobPrescricao*, poo::Produto*>,
              "MedicamentoSobPrescricao tem de herdar publicamente de Produto");
static_assert(std::is_convertible_v<poo::MedicamentoControlado*, poo::Produto*>,
              "MedicamentoControlado tem de herdar publicamente de Produto");


static_assert(std::is_base_of_v<poo::Produto, poo::MedicamentoControlado>,
              "MedicamentoControlado tem de derivar de Produto");
static_assert(std::is_base_of_v<poo::Escrituravel, poo::MedicamentoControlado>,
              "MedicamentoControlado tem de derivar de Escrituravel");


static_assert(std::is_base_of_v<std::vector<std::unique_ptr<poo::Produto>>, poo::Estoque>,
              "Estoque tem de derivar de vector<unique_ptr<Produto>>");
static_assert(!std::is_convertible_v<poo::Estoque*, std::vector<std::unique_ptr<poo::Produto>>*>,
              "Estoque nao pode converter para vector: a heranca tem de ser privada");

#endif 