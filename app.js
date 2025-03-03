const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
})

app.listen(port, () => {
  console.log(`Scheduler app listening on port ${port}`)
})