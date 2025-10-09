# 🖼️ Logo Scraper API

**Logo Scraper API** é um microserviço desenvolvido que permite obter automaticamente o logótipo (ou ícone principal) de qualquer website público, fornecendo apenas o respetivo URL.  

Este projeto foi construído com **Node.js**, **Express**, **Axios** e **Cheerio**, garantindo uma arquitetura simples, eficiente e facilmente extensível.

---

## 🚀 Funcionalidades

- Extrai o logótipo principal de um website a partir do seu HTML.
- Suporta:
  - `<link rel="icon">`, `<link rel="apple-touch-icon">`
  - `meta[property="og:image"]`, `meta[name="twitter:image"]`
  - Imagens com identificadores “logo”, “brand”, etc.
  - Fallback automático para `/favicon.ico`
- Retorna o URL direto da imagem.
- Timeout e validação básica de URLs para evitar abusos.
- Ideal para integrações em dashboards, gestores de subscrições, ou ferramentas de enriquecimento de dados.

---

## 🧰 Tecnologias Utilizadas

- **Node.js**
- **Express.js**
- **Axios**
- **Cheerio**
- **valid-url**

---

## ⚙️ Instalação

1. Clonar o repositório:
   ```bash
   git clone https://github.com/taleex/logo-scraper.git
   cd logo-scraper
````

2. Instalar dependências:

   ```bash
   npm install
   ```

3. Executar o servidor:

   ```bash
   node index.js
   ```

4. O serviço estará disponível em:

   ```
   http://localhost:3000
   ```

---

## 🔗 Endpoint

### `GET /logo`

**Descrição:** Retorna o URL do logótipo principal encontrado no website.

#### Parâmetros

| Nome  | Tipo   | Obrigatório | Descrição                                          |
| ----- | ------ | ----------- | -------------------------------------------------- |
| `url` | string | ✅           | URL completo do website (ex: `https://github.com`) |

#### Exemplo de request

```
GET http://localhost:3000/logo?url=https://github.com
```

#### Exemplo de resposta

```json
{
  "logo": "https://github.githubassets.com/favicons/favicon.png"
}
```

#### Códigos de resposta

| Código | Descrição                           |
| ------ | ----------------------------------- |
| `200`  | Logo encontrado com sucesso         |
| `400`  | Parâmetro `url` inválido ou ausente |
| `500`  | Erro interno ao processar o pedido  |

---

## 🧱 Estrutura do Projeto

```
📦 logo-scraper
 ┣ 📄 index.js         # Código principal do servidor
 ┣ 📄 package.json     # Configuração do projeto
 ┗ 📄 README.md        # Este ficheiro
```

---

## 🔒 Segurança Recomendada

Para produção, recomenda-se:

* Limitar tamanho máximo do HTML recebido.
* Bloquear endereços IP internos (para evitar SSRF).
* Adicionar *rate limiting* e cache.
* Validar o tipo de conteúdo (apenas imagens).
* Usar HTTPS em deploy.


## 🧾 Créditos

Desenvolvido com ❤️ por **[Taleex](https://taleex.netlify.app/)**



