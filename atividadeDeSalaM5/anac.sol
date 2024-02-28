// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract documentoANAC {
    address public owner; // Variável que armazena o endereço do dono do contrato
    uint256 public idade; // Variavel de estado

    constructor(){  // Construtor inicializa a idade como 18 e define o dono como o endereço que fez a implantação
        idade = 18; // idade inicial definida
        owner = msg.sender; // Define o endereço do dono como o endereço do criador do contrato
    }

       modifier apenasDono() {
        require(msg.sender == owner, "Apenas o dono do contrato pode executar esta funcao");
        _; // Continua a execução da função após a verificação ser bem-sucedida
    }

    // Função para definir a idade, só pode ser executada pelo dono do contrato
    function setIdade (uint256 x) public apenasDono() {
        idade = x;
    }

    // Função para obter a idade
    function getIdade() public view returns (uint256) {
        return idade;
    }
}



