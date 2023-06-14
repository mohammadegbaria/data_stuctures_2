#include "prime.h"

// helper function to check if a number is prime
bool is_prime(int n) {
  if (n <= 1) {
    return false;
  }
  if (n <= 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  for (int i = 5; i <= sqrt(n); i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

int next_prime(int n) {
  if (n <= 1) {
    return 2;
  }

  if (n == 2) {
    return 3;
  }

  // check if n is even
  if (n % 2 == 0) {
    // if it is, check if n + 1 is prime
    n++;
  } else {
    // if n is odd, check if n + 2 is prime
    n += 2;
  }

  // if n is already prime, return it
  if (is_prime(n)) {
    return n;
  }

  // otherwise, keep checking odd numbers until we find a prime one
  while (true) {
    n += 2;

    // check if n is divisible by 3
    if (n % 3 == 0) {
      continue;
    }

    // check if n is divisible by 5
    if (n % 5 == 0) {
      continue;
    }

    // check if n is divisible by 7
    if (n % 7 == 0) {
      continue;
    }

    // if n is not divisible by 3, 5, or 7, check if it is prime
    if (is_prime(n)) {
      return n;
    }
  }
}

int prev_prime(int n) {
  if (n <= 1) {
    return n;
  }

  if (n == 2) {
    return n;
  }

  // check if n is even
  if (n % 2 == 0) {
    // if it is, check if n + 1 is prime
    n--;
  } else {
    // if n is odd, check if n + 2 is prime
    n -= 2;
  }

  // if n is already prime, return it
  if (is_prime(n)) {
    return n;
  }

  // otherwise, keep checking odd numbers until we find a prime one
  while (true) {
    n -= 2;

    // check if n is divisible by 3
    if (n % 3 == 0) {
      continue;
    }

    // check if n is divisible by 5
    if (n % 5 == 0) {
      continue;
    }

    // check if n is divisible by 7
    if (n % 7 == 0) {
      continue;
    }

    // if n is not divisible by 3, 5, or 7, check if it is prime
    if (is_prime(n)) {
      return n;
    }
  }
}

int closer_prime(int n)
{
    int prevPrime = prev_prime(n);
    int nextPrime = next_prime(n);

    int prev_gap = std::abs(n - prevPrime);
    int next_gap = std::abs(n - nextPrime);

    return (prev_gap < next_gap)? prevPrime : nextPrime;

}