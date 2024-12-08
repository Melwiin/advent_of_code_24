const { MinHeap } = require('@datastructures-js/heap');

var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('input.txt')
});
  
let leftList = new MinHeap()
let rightList = new MinHeap()

let result = 0;

lineReader.on('line', function(line) {
    var elements = line.split('   ');
    leftList.insert(elements[0])
    rightList.insert(elements[1])
});

lineReader.on('close', function() {
    while(!leftList.isEmpty()) {
        result += Math.abs(leftList.extractRoot() - rightList.extractRoot())
    }
    console.log(result);
});

