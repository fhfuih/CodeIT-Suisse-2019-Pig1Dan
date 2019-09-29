# CodeIT Suisse 2019 Pig1Dan

## Run

After installing dependecies by `npm install` (or `yarn install`), run with `npm start`.

By default, after starting the server, one can visit `localhost:3000/hello?name={optional}` and see `hello {name}|world!`.

## Structure

In the express boilerplate:

- Winston logger
  - `warn`+ -> file
  - `info`+ -> console
- Body Parser
  - urlencoded (extended)
  - json (not strict)
- CORS
  - allow all
  - allow all pre-flight
- Helmet
- Nodemon
- Styling Enforcement
  - Eslint: standard JS
  - Prettier: default
    - Single quotes

## Python adapter

See [python-shell](https://www.npmjs.com/package/python-shell)

## C++ adapter

See [this Chinese tutorial](https://juejin.im/post/5af58b81f265da0b767d8837)? Or use shell subprocess and JSON format as data I/O.

## Result

Final Score : 7333 | Rank #1 in both HK and Singapore

Cheers!

![Scoreboard](https://github.com/fhfuih/CodeIT-Suisse-2019-Pig1Dan/blob/master/pic/result.png)
