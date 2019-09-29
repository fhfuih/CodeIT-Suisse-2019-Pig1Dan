
const fs = require('fs');

function findEnemyTables(tables, guest, list) {
  let arr = [];
  for (let i in tables) {
    if (hasRelationTable(tables[i], guest, list)) {
      arr.push(i);
    }
  }
  return arr;
}
function inTable(table, guest) {
  for (let i in table) {
    if (table[i] === guest) {
      return true;
    }
  }
  return false;
}
function checkEnemyinTable(table, list) {
  for (let i in list) {
    if (table.includes(list[i][0]) && table.includes(list[i][1])) {
      return true;
    }
  }
  return false;
}
function findRelations(guest, list) {
  const arr = [];
  for (let i in list) {
    if (list[i].includes(guest)) {
      arr.push(list[i][0] === guest ? list[i][1] : list[i][0]);
    }
  }
  return arr;
}
function removeGuest(guests, guest) {
  let index = -1;
  for (let i in guests) {
    if (guests[i] === guest) {
      index = i;
    }
  }
  guests.splice(index, 1);
  return guests;
}
function hasRelationTable(table, guest, list) {
  for (let i in table) {
    for (let j in list) {
      if (list[j].includes(guest) && list[j].includes(table[i])) {
        return true;
      }
    }
  }
  return false;
}
function hasRelationTables(tableList, guest, list) {
  for (let i in tableList) {
    for (let j in tableList[i]) {
      for (let k in list) {
        if (list[k].includes(guest) && list[k].includes(tableList[i][j])) {
          return i;
        }
      }
    }
  }
  return -1;
}

// function wedNightmare(req, res) {
//   const cases = req.body;
//   const output = [];
//   for (let i = 0; i < cases.length; i += 1) {
//     // Initialize
//     output.push({});
//     output[i].test_case = cases[i].test_case;
//     output[i].allocation = [];
//     const guests = [];
//     for (let j = 0; j < cases[i].guests; j += 1) {
//       guests.push(j + 1);
//     }
//     const tables = [];
//     for (let j = 0; j < cases[i].tables; j += 1) {
//       tables.push([]);
//     }
//     let satisfy = true;
//     // Start Arranging
//     while (guests.length > 0) {
//       const guest = guests.shift();
//       const friendTable = hasRelationTables(tables, guest, cases[i].friends);
//       const familyTable = hasRelationTables(tables, guest, cases[i].families);
//       if (friendTable !== -1) {
//         if (hasRelationTable(tables[friendTable], guest, cases[i].enemies)) {
//           satisfy = false;
//           break;
//         } else {
//           tables[friendTable].push(guest);
//         }
//       } else if (familyTable !== -1) {
//         if (hasRelationTable(tables[familyTable], guest, cases[i].enemies)) {
//           satisfy = false;
//           break;
//         } else {
//           tables[familyTable].push(guest);
//         }
//       } else {
//         let tableNum = -1;
//         for (let j = 0; j < tables.length; j += 1) {
//           if (!tables[j].length) {
//             tables[j].push(guest);
//             tableNum = j;
//             break;
//           } else {
//             if (!hasRelationTable(tables[j], guest, cases[i].enemies)) {
//               tables[j].push(guest);
//               tableNum = j;
//               break;
//             }
//           }
//         }
//         if (tableNum === -1) {
//           satisfy = false;
//           break;
//         }
//       }
//     }
//     // Normalize
//     output[i].satisfiable = satisfy;
//     output[i].allocation = [];
//     if (satisfy) {
//       for (let j in tables) {
//         if (tables[j].length) {
//           for (let k in tables[j]) {
//             output[i].allocation.push([tables[j][k], parseInt(j) + 1]);
//           }
//         }
//       }
//     }
//   }
//   fs.writeFile("./output.txt", JSON.stringify(output, null, "\t"), function(err) {
//     if(err) {
//         return console.log(err);
//     }
//     console.log("The file was saved!");
//   });
//   res.send(output);
// }

function wedNightmare(req, res) {
  const cases = req.body;
  const output = [];
  for (let i = 0; i < cases.length; i += 1) {
    output.push({});
    output[i].test_case = cases[i].test_case;
    output[i].allocation = [];
    let guests = [];
    for (let j = 0; j < cases[i].guests; j += 1) {
      guests.push(j + 1);
    }
    const tables = [];
    for (let j = 0; j < cases[i].tables; j += 1) {
      tables.push([]);
    }
    let satisfy = true;
    while (guests.length > 0) {
      const guest = guests.shift();
      let tableNum = -1;
      for (let j in tables) {
        if (!hasRelationTable(tables[j], guest, cases[i].enemies)) {
          tables[j].push(guest);
          tableNum = j;
          const friends = findRelations(guest, cases[i].friends);
          const families = findRelations(guest, cases[i].families);
          console.log(friends);
          for (let k in friends) {
            if (!inTable(tables[j], friends[k])) {
              tables[j].push(friends[k]);
              guests = removeGuest(guests, friends[k]);
              if (checkEnemyinTable(tables[j], cases[i].enemies)) {
                satisfy = false;
                break;
              }
            }
          }
          for (let k in families) {
            if (!inTable(tables[j], families[k])) {
              tables[j].push(families[k]);
              guests = removeGuest(guests, families[k]);
              if (checkEnemyinTable(tables[j], cases[i].enemies)) {
                satisfy = false;
                break;
              }
            }
          }
          break;
        }
      }
      if (tableNum === -1) {
        satisfy = false;
        break;
      }
    }
    console.log(tables);
    output[i].satisfiable = satisfy;
    output[i].allocation = [];
    if (satisfy) {
      for (let j in tables) {
        if (tables[j].length) {
          for (let k in tables[j]) {
            output[i].allocation.push([tables[j][k], parseInt(j) + 1]);
          }
        }
      }
    }
  }
  res.send(output);
}

module.exports = wedNightmare;
