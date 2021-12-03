// See: Advent of Code 2021, Day 3: Binary Diagnostics
// Made by: krauluk1

var fs = require('fs');
const { getSystemErrorMap } = require('util');

// Taks 1
const binary_conv = (input) => parseInt(input, 2);

const read_txt1 = (path) => {
    return new Promise((resolve, reject) => {
        fs.readFile(path, 'utf-8', (err, data) => {
            if (err) throw err;
            resolve(data.split(/\r?\n/));
        });
    });
} 

const analyse_input1 = (inp) => {
    return new Promise((resolve, reject) => {
        var amount = inp[0].toString().length;
        // zero_array, one_array
        let num_array = [new Array(amount).fill(0), new Array(amount).fill(0)];
        // epsilon, gamma
        let val_array = [new Array(amount).fill(0), new Array(amount).fill(0)];

        for(var line = 0; line < inp.length; line++){
            let n = inp[line].toString().split('');
            for(var numb = 0; numb < amount; numb++)
            {
                let p = n[numb];
                if(p === '1'){
                    num_array[1][numb]++;
                }else if(p === '0'){
                    num_array[0][numb]++;
                }
            }
        }

        for(var i = 0; i < amount; i++){
            if(num_array[0][i] > num_array[1][i]){
                val_array[1][i] = '0';
                val_array[0][i] = '1';

            }else{
                val_array[1][i] = '1';
                val_array[0][i] = '0';
            }
        }

        
        val_array[1] = val_array[1].join('');
        val_array[0] = val_array[0].join('');

        resolve(val_array);
    });
}


async function test_1 (reader, analyser, converter, path = "Day_3/input.txt") {
    try{
        var data = await reader(path);
    }catch(err){
        console.log(err);
    }

    try{
        var rate = await analyser(data);
    }catch(err){
        console.log(err);
    }

    console.log("Epsilon", rate[0], "Gamma", rate[1]);
    console.log("Task 1 Solution: ", converter(rate[0])*converter(rate[1]));
}

test_1(read_txt1, analyse_input1, binary_conv);

// Test 2

async function test_2 (reader, analyser, converter, path = "Day_3/input.txt"){
    try{
        var data = await reader(path);
    }catch(err){
        console.log(err);
    }

    
    let number_len = data[0].toString().length;

    let oxygen_rate = JSON.parse(JSON.stringify(data));
    for(let i = 0; i < number_len; i++){
        try{
            var rate = await analyser(oxygen_rate);
        }catch(err){
            console.log(err);
        }

        if(oxygen_rate.length <= 1){
            break;
        }

        for(let j = oxygen_rate.length - 1; j >= 0; j--){
            if(rate[1][i] !== oxygen_rate[j][i]){
                oxygen_rate.splice(j, 1);
            }
        }
    }
    console.log("oxygen", oxygen_rate[0]);
    
    let co2_rate = JSON.parse(JSON.stringify(data));
    for(let i = 0; i < number_len; i++){
        try{
            var rate = await analyser(co2_rate);
        }catch(err){
            console.log(err);
        }
        
        if(co2_rate.length <= 1){
            break;
        }

        for(let j = co2_rate.length - 1; j >= 0; j--){
            if(rate[0][i] !== co2_rate[j][i]){
                co2_rate.splice(j, 1);
            }
        }
    }
    console.log("co2", co2_rate[0]);


    console.log("Task 2 Solution: ", converter(oxygen_rate[0])*converter(co2_rate[0]));
}

test_2(read_txt1, analyse_input1, binary_conv);
