'use strict';

function errorResponse({ message, stack }) {
  return {
    error: {
      message,
      stack: process.env.NODE_ENV === 'production' ? undefined : stack
    }
  };
}

module.exports = errorResponse;
