const express = require('express');
const app = express();

app.use((req, res, next) =>{
  console.log(`${req.method} ${req.url}`);
});

app.get("/", (req, res) => {
  res.send("Express");
})

const PORT = 3000;
const HOST = "127.0.0.1";

app.listen(PORT, HOST, () => {
  console.log (`Express server is running at http://${HOST}:${PORT}`)
});