# CodeIT Suisse 2019 Pig1Dan

## Run

After installing dependecies by `npm install` (or `yarn install`), run with `npm start`.

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
