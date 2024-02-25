// SPDX-License-Identifier: MIT 
// tentando ir além no choro aaaaaaa
pragma solidity ^0.8.0;

contract ProdutoContract {
    struct Produto {
        string nome;
        uint256 preco;
    }

    mapping(uint256 => Produto) public produtos;

    function adicionarProduto(uint256 sku, string memory nome, uint256 preco) external {
        produtos[sku] = Produto(nome, preco);
    }

    function obterNomeDoProduto(uint256 sku) external view returns (string memory) {
        return produtos[sku].nome;
    }
}
