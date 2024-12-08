var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('input.txt')
});

let leftList = [];
let rightList = [];

result = 0;

lineReader.on('line', function(line) {
    var elements = line.split('   ');
    leftList.push(elements[0])
    rightList.push(elements[1])    
});

lineReader.on('close', function() {
    leftList.forEach(num => {
        result += num * rightList.filter((e) => { return e == num }).length
    })
    console.log(result)
});