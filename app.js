const express = require('express');
const https = require('https');
const fs = require('fs');
const WebSocket = require('ws');
const ffi = require('ffi-napi');
const ref = require('ref-napi');
const StructType = require('ref-struct-di')(ref);
const path = require('path');

const app = express();
const port = 3000;

const sslOptions = {
  key: "",
  cert: "" 
};

const server = https.createServer(sslOptions, (req, res) => {
  res.writeHead(200);
  res.end('Command server is running');
});

const CommandT = StructType({
  'commandId': ref.types.CString,
  'issuedBy': ref.types.CString,
  'issuedAt': ref.types.CString,
  'priority': ref.types.CString,
  'jwt': ref.types.CString,
  'operation': ref.types.CString,
  'deltaV': ref.types.double,
  'axis': ref.types.CString
});

const CommandTPtr = ref.refType(CommandT);
const CommandTPtrPtr = ref.refType(CommandTPtr);

app.get('/', (req, res) => {
})

app.listen(port, () => {
  console.log(`Scheduler app listening on port ${port}`);
})