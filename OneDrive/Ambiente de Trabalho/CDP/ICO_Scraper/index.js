const express = require("express");
const axios = require("axios");
const cheerio = require("cheerio");
const validUrl = require("valid-url");

const app = express();
const PORT = 3000;

app.get("/logo", async (req, res) => {
  const { url } = req.query;

  if (!url || !validUrl.isWebUri(url)) {
    return res
      .status(400)
      .json({ error: 'Parâmetro "url" inválido ou ausente.' });
  }

  try {
    // Obter o HTML
    const { data } = await axios.get(url, {
      headers: { "User-Agent": "LogoScraper/1.0" },
      timeout: 5000,
    });

    // Fazer parse do HTML
    const $ = cheerio.load(data);

    // Procurar possíveis logos
    const candidates = [];

    // <link rel="icon"> e semelhantes
    $('link[rel*="icon"]').each((i, el) => {
      const href = $(el).attr("href");
      if (href) candidates.push(new URL(href, url).href);
    });

    // Meta OG image
    const og = $('meta[property="og:image"]').attr("content");
    if (og) candidates.push(new URL(og, url).href);

    // Img com “logo” no nome/classe
    $("img").each((i, el) => {
      const src = $(el).attr("src");
      const alt = $(el).attr("alt") || "";
      const cls = $(el).attr("class") || "";
      if ((alt + cls + src).toLowerCase().includes("logo")) {
        candidates.push(new URL(src, url).href);
      }
    });

    // Fallback para favicon.ico
    candidates.push(new URL("/favicon.ico", url).href);

    // Escolher o primeiro válido
    const logoUrl = candidates[0];
    res.json({ logo: logoUrl });
  } catch (err) {
    res
      .status(500)
      .json({ error: "Erro ao obter logo.", details: err.message });
  }
});

app.listen(PORT, () =>
  console.log(`Servidor a correr em http://localhost:${PORT}`)
);
