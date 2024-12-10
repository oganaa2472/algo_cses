import java.util.Scanner;

public class WeirdAlgorithm {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Read the input number
        long n = sc.nextLong(); // Using long to handle larger values

        // Print the initial number
        System.out.print(n + " ");

        // Loop until n becomes 1
        while (n != 1) {
            if (n % 2 == 0) {
                n /= 2; // If n is even, divide by 2
            } else {
                n = n * 3 + 1; // If n is odd, multiply by 3 and add 1
            }

            // Print the current value of n
            System.out.print(n + " ");
        }

        sc.close();
    }
}
