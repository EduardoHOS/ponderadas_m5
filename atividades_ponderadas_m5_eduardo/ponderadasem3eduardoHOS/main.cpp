#include <iostream>
#include <string>

// Para o tratamento de colições, usei a referencia desse video: https://www.youtube.com/watch?v=N4uQ6oq0VVc&t=1162s

#define TAM 31 // Tamanho da tabela hash

// Definição da classe Produto
class Produto {
public:
    // Construtor que inicializa o SKU e o nome do produto
    Produto(int SKU, const std::string& nome) : SKU(SKU), nome(nome) {}

    // Métodos para obter o SKU e o nome do produto
    int getRa() const { return SKU; }
    const std::string& getNome() const { return nome; }

private:
    int SKU; // Stock Keeping Unit
    std::string nome;
};

// Classe TabelaHash para armazenar os produtos
class TabelaHash {
public:
    // Construtor
    TabelaHash() {
        estrutura = new Produto*[TAM];
        for (int i = 0; i < TAM; ++i)
            estrutura[i] = nullptr; // Inicializa todas as posições da tabela como nulas
    }

    // Destrutor para liberar memória alocada dinamicamente
    ~TabelaHash() {
        for (int i = 0; i < TAM; ++i)
            delete estrutura[i]; // Deleta cada objeto Produto
        delete[] estrutura; // Deleta o array de ponteiros para Produto
    }

    // Função para inserir um produto na tabela hash
    void inserirProduto(const Produto& produto) {
        int indice = calcularIndice(produto.getRa()); // Calcula o índice na tabela para o produto
        while (estrutura[indice] != nullptr) { // Enquanto houver uma colisão
            indice = funcaoHash(indice + 1); // Resolve a colisão usando sondagem linear, apredi no video hihiiiii
        }
        estrutura[indice] = new Produto(produto); // Insere o produto na posição encontrada
    }

    // Função para buscar um produto na tabela hash
Produto* buscarProduto(int SKU) {
    int indice = calcularIndice(SKU);
    while (estrutura[indice] != nullptr) {
        if (estrutura[indice]->getRa() == SKU)
            return estrutura[indice];
        indice = funcaoHash(indice + 1);
    }
    return nullptr;
}

void removerProduto(int SKU) {
    int indice = calcularIndice(SKU);
    while (estrutura[indice] != nullptr) {
        if (estrutura[indice]->getRa() == SKU) {
            delete estrutura[indice];
            estrutura[indice] = nullptr;
            return;
        }
        indice = funcaoHash(indice + 1);
    }
}
private:
    Produto** estrutura; // Ponteiro para um array de ponteiros para Produto

    // Função para calcular o índice na tabela hash usando o SKU
    int calcularIndice(int SKU) const {
        return SKU % TAM; // Usa uma função de hash simples para calcular o índice
    }

    // Função de hash para resolver colisões
    int funcaoHash(int chave) const {
        return chave % TAM; // Resolve colisões
    }
};

int main() {
    // Cria tabela hash
    TabelaHash tabela;

    // Caso de teste 1: Inserir um produto e buscar por ele
    Produto produto1(12345, "Caneta");
    tabela.inserirProduto(produto1);
    Produto* produtoEncontrado1 = tabela.buscarProduto(12345);
    if (produtoEncontrado1)
        std::cout << "Caso de teste 1: Produto encontrado: SKU " << produtoEncontrado1->getRa() << ", Nome: " << produtoEncontrado1->getNome() << std::endl;
    else
        std::cout << "Caso de teste 1: Produto não encontrado." << std::endl;

    // Caso de teste 2: Inserir dois produtos com o mesmo SKU
    Produto produto2(67890, "Mochila");
    Produto produto3(67890, "Mochila do Inteli");
    tabela.inserirProduto(produto2);
    tabela.inserirProduto(produto3);
    Produto* produtoEncontrado2 = tabela.buscarProduto(67890);
    if (produtoEncontrado2)
        std::cout << "Caso de teste 2: Produto encontrado: SKU " << produtoEncontrado2->getRa() << ", Nome: " << produtoEncontrado2->getNome() << std::endl;
    else
        std::cout << "Caso de teste 2: Produto não encontrado." << std::endl;

    // Caso de teste 3: Buscar por um produto que não existe
    Produto* produtoEncontrado3 = tabela.buscarProduto(99999);
    if (produtoEncontrado3)
        std::cout << "Caso de teste 3: Produto encontrado: SKU " << produtoEncontrado3->getRa() << ", Nome: " << produtoEncontrado3->getNome() << std::endl;
    else
        std::cout << "Caso de teste 3: Produto não encontrado.(era minha sanidade ops...)" << std::endl;

    // Caso de teste 4: Inserir e buscar múltiplos produtos
    Produto produto4(11111, "Lapis");
    Produto produto5(22222, "Canetinha");
    tabela.inserirProduto(produto4);
    tabela.inserirProduto(produto5);
    Produto* produtoEncontrado4 = tabela.buscarProduto(11111);
    if (produtoEncontrado4)
        std::cout << "Caso de teste 4: Produto encontrado: SKU " << produtoEncontrado4->getRa() << ", Nome: " << produtoEncontrado4->getNome() << std::endl;
    else
        std::cout << "Caso de teste 4: Produto não encontrado." << std::endl;


  // Caso de teste 5: Eliminar um produto da tabela
  TabelaHash tabelaComProduto;
  Produto produto6(33333, "Branquinho");
  tabelaComProduto.inserirProduto(produto6);

  // Verifica se o produto foi inserido corretamente
  Produto* produtoAntesDaRemocao = tabelaComProduto.buscarProduto(33333);
  if (produtoAntesDaRemocao) {
      std::cout << "Caso de teste 5: Produto encontrado antes da remoção: SKU " << produtoAntesDaRemocao->getRa() << ", Nome: " << produtoAntesDaRemocao->getNome() << std::endl;
  } else {
      std::cout << "Caso de teste 5: Produto não encontrado antes da remoção." << std::endl;
  }

  // Remove o produto da tabela
  tabelaComProduto.removerProduto(33333);

  // Verifica se o produto foi removido com sucesso
  Produto* produtoAposRemocao = tabelaComProduto.buscarProduto(33333);
  if (produtoAposRemocao) {
      std::cout << "Caso de teste 5: Produto encontrado após a remoção: SKU " << produtoAposRemocao->getRa() << ", Nome: " << produtoAposRemocao->getNome() << std::endl;
  } else {
      std::cout << "Caso de teste 5: Produto não encontrado após a remoção." << std::endl;
  }

    return 0;
}
