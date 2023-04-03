// loading libraries
// const { SerialPort } = require('serialport')
var express = require('express');
var app = express();


// try {
// setting up serial communication - make sure the port number is correct. 
// const { ReadlineParser } = require('@serialport/parser-readline')
// const port = new SerialPort({ path: '/dev/cu.usbmodem2101', baudRate: 9600 })
// const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))
// parser.on('data', console.log)
// console.log("Sucessfully connected to Arduino");
// } catch (err) {
//   console.log('Error connecting to Arduino:', err.message);
// }


//this line is required to connect the css stylesheet (no idea why)
app.use(express.static(__dirname));

// HOME page - sends L (=low) to Arduino
app.get('/', function (req, res) {
  res.sendFile('HTML/index.html', { root: __dirname })
  // writeDataToArduino("L");
});

// INFORMATION page - sends nothing to Arduino
app.get('/info', function (req, res) {
  res.sendFile('HTML/info.html', { root: __dirname })
  // writeDataToArduino("L");
});

// Search Engine Selection page - sends L (=low) to Arduino
app.get('/selection', function (req, res) {
  res.sendFile('HTML/selection.html', { root: __dirname })
  // writeDataToArduino("L");
});

// Google News - G
app.get('/googlenews', function (req, res) {
  res.sendFile('HTML/SearchEngines/googlenews.html', { root: __dirname })
  // writeDataToArduino("G");
});

// BBC - B
app.get('/bbc', function (req, res) {
  res.sendFile('HTML/SearchEngines/bbc.html', { root: __dirname })
  // writeDataToArduino("B");
});

// The New York Times - N
app.get('/newyorktimes', function (req, res) {
  res.sendFile('HTML/SearchEngines/newyorktimes.html', { root: __dirname })
  // writeDataToArduino("N");
});

// Newsweek - B
app.get('/newsweek', function (req, res) {
  res.sendFile('HTML/SearchEngines/newsweek.html', { root: __dirname })
  // writeDataToArduino("B");
});

// Wall Steet Journal - W
app.get('/wallstreetjournal', function (req, res) {
  res.sendFile('HTML/SearchEngines/wallstreetjournal.html', { root: __dirname })
  // writeDataToArduino("W");
});

// Fox News - F
app.get('/foxnews', function (req, res) {
  res.sendFile('HTML/SearchEngines/foxnews.html', { root: __dirname })
  // writeDataToArduino("F");
});


// function writeDataToArduino(data) {
//   try {
//     port.write(data, function (err) {
//       if (err) {
//         return console.log('Error on write: ', err.message);
//       }
//       console.log('Data written to Arduino: ' + data);
//     });
//   } catch (err) {
//     console.log('Error writing data to Arduino:', err.message);
//   }
// }

// to set up the localhost. 
var server = app.listen(3000, function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Example app listening at http://%s:%s', host, port);
});

