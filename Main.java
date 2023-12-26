import java.awt.*;
import java.text.FieldPosition;
import java.text.NumberFormat;
import java.text.ParsePosition;
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

import static java.lang.Math.round;

public class Main{
   public static void main(String[] args) {

       /*System.out.println("Vanakkam di Maapla, Seattle la irunthu!!");
       byte age= 45; //primitive types
       int age_2 = age + 45; //primitive types
       int a = age_2 - 96; //primitive types
       System.out.println( age + age_2 + a);
       Date now = new Date();  //reference types
//krikkkkkkk
       //reference types - changeable values even after assigning
       //System.out.println(now);
       Point point1 = new Point(1,1);
       Point point2 = point1;
       point1.y = 34;
       point2.x = 67;
       System.out.println(point2.x + point1.y);*/

       //strings are reference types in java, even though they seem like primitive types.
       /*String name = "Rishi" + "Kiran";
       System.out.println(name.startsWith("an"));
       System.out.println("Rishi"+ " "+"Kiran");
       String name2 = "Rishi"+ " "+"Kiran";
       int length = name2.length();
       System.out.println(length);*/

       //long method to implement arrays
       /*int [] numbers = new int[5];
       numbers[1] = 2;
       numbers[0] = 1;
       numbers[4] = 5;
       numbers[3] = 6;
       Arrays.sort(numbers); //sort method implementation
       System.out.println(Arrays.toString(numbers));

       //short method
       int [] numbers2 = {2,3,4,5,6};
       System.out.println(Arrays.toString(numbers2));

       int [][] numbers3 = new int [3] [3];
       numbers3 [0] [2] = 1;
       numbers3 [0] [1] = 5;
       numbers3 [1] [1] = 3;
       System.out.println(Arrays.deepToString(numbers3)); //2 dimensional array

       int [][][] numbers4 = new int [3] [3] [3];
       numbers4 [0] [2] [2] = 1;
       numbers4 [0] [1] [1] = 5;
       numbers4 [2] [0] [0] = 3;
       System.out.println(Arrays.deepToString(numbers4)); //multi-dimensional arrays

       final float pi = 3.14F;
       //pi = 1;
       System.out.println(pi); //constants

       double result = (double)10/(double)3;
       System.out.println(result);
       int x=2;
       int y=++x;
       x += 2; //augmented assignment operator
       x /= 2;
       System.out.println(x);
       System.out.println(y);

       NumberFormat result1 = NumberFormat.getPercentInstance();
       String result2= result1.format(12.369);
       System.out.println(result2);

       Scanner scanner = new Scanner(System.in);
       System.out.print("Enter your Name: ");
       String name = scanner.nextLine().trim();
       System.out.println("your are " + name); //input through scanner



       //module 2 control flow
       Scanner scanner = new Scanner(System.in);
       System.out.print("Enter X= ");
       Integer x = scanner.nextInt();
       System.out.print("Enter Y= ");
       Integer y = scanner.nextInt();
       //String result = (x==y)? "Both are same" : "Both are not same"; //monisha's method
       String result2 = x.equals(y)? "Both are same" : "Both are not same"; //monisha's method

       System.out.print(result2);
       Scanner scanner = new Scanner(System.in);
       System.out.print("How's the weather mate? ");
       float temperature = scanner.nextFloat();
       boolean isWarm = temperature >= 20 && temperature <= 80;
       System.out.println(isWarm);


       //switch statements
       Scanner scanner = new Scanner(System.in);
       System.out.print("guest or moderator or admin? :");
       String role = scanner.next().trim();
       switch (role){
           case "admin":
               System.out.println("Nee than pa admineyyy");
               break;
           case "moderator":
               System.out.println("inthama moderator'eyyy");
               break;
           default :
               System.out.println(" Guest ah da nee..");
       }

       Scanner scanner = new Scanner(System.in);
       System.out.println("Number: ");
       int number = scanner.nextInt().trim();
       switch (number) {
           case (number / 5 == 0):
               System.out.println("Fizz");
               break;
           case (number / 3 == 0):
               System.out.println("Buzz");
               break;
           case ((number / 3 == 0) && (number / 5 == 0)):
               System.out.println("FizzBuzz");
               break;
           default:
               System.out.println(number);

       }
       Scanner scanner = new Scanner(System.in);

       for (int i = 0; i < 10; i++) {
           System.out.print("Number: ");

           if (scanner.hasNextInt()) {
               int number = scanner.nextInt();

               if ((number % 3 == 0) && (number % 5 == 0)) {
                   System.out.println("FizzBuzz");
               } else if (number % 5 == 0) {
                   System.out.println("Fizz");
               } else if (number % 3 == 0) {
                   System.out.println("Buzz");
               } else {
                   System.out.println(number);
               }
               break;
           }

           else {
               System.out.println("Please stick to integers");
               // Consume the invalid input
               scanner.next();
           }
       }
      //while implementation
      String input ="";
      Scanner scanner = new Scanner(System.in);
      while(!input.equals("quit")){
         System.out.print("Input: ");
         input = scanner.next().toLowerCase();
      }
      do {
         System.out.print("Input: ");
         input = scanner.next().toLowerCase();
      }
      while(!input.equals("quit"));*/

      /************************/
      //mortgage calculator ( exception handling using do-while)
      /************************/

      /*Scanner scanner = new Scanner(System.in);

      // Principal input
      int principal;
      do {
         System.out.print("Principal ($1k - $1m): $ ");
         principal = scanner.nextInt();
         if(principal >= 1000 && principal <= 1000000)
            break;
         System.out.println("Enter a number between $1k to $1000000");
      } while (true);

      // Annual interest rate input
      float annualInterestRate;
      do {
         System.out.print("Annual Interest Rate (0-30%): ");
         annualInterestRate = scanner.nextFloat();
         if (annualInterestRate > 0 && annualInterestRate<= 30)
            break;
         System.out.println("Enter a value between 0 and less than or equal to 30");
      } while (true);

      // Period in years input
      int periodYears;
      do {
         System.out.print("Period (1-30 years): ");
         periodYears = scanner.nextInt();
         if (periodYears > 0 && periodYears <= 30)
            break;
         System.out.println("Enter a value between 0 and less than or equal to 30");
      } while (true);

      //math section

      int n = periodYears * 12; // periodMonths
      double r = annualInterestRate / (12 * 100); // monthlyInterestRate
      // math implementation of (1+r)
      double r1 = (1 + r);
      // math implementation of (1+r)^n
      double r2 = Math.pow(r1, n);
      // math implementation of r((1+r)^n)
      double r3 = r * r2;
      // math implementation of ((1+r)^n) - 1
      double r4 = r2 - 1;
      // now r3/r4
      double r5 = r3 / r4;
      // Mortgage calculation
      double mortgage = principal * r5;
      mortgage = Math.round(mortgage * 100.00) / 100.00;
      System.out.println("Your mortgage is: $ " + mortgage);*/



      /************************/
      //mortgage calculator ( exception handling using while)
      /************************/

      /*float principal = 0;
      float annualInterestRate= 0;
      float periodYears;
      Scanner scanner = new Scanner(System.in);
      while(true) {
         System.out.print("Principal ($1k - $1m): $ ");
         principal = scanner.nextFloat();
         //principal = (int) principal;
         //principal = Math.round(principal);
         //System.out.println(principal);
         if(principal >= 1000 && principal <= 1000000)
            break;
         System.out.println("Enter a number between $1k to $1000000");
      }
      while (true) {
         System.out.print("Annual Interest Rate: ");
         annualInterestRate = scanner.nextFloat();
         if (annualInterestRate > 0 && annualInterestRate<= 30)
            break;
         System.out.println("Enter a value between 0 and less than or equal to 30");
      }
      while (true) {
         System.out.print("Period (Years): ");
         periodYears = scanner.nextFloat();
         if (periodYears > 0 && periodYears <= 30)
            break;
         System.out.println("Enter a value between 0 and less than or equal to 30");
      }


      //math section

      float n = periodYears * 12; // periodMonths
      double r = annualInterestRate / (12 * 100); // monthlyInterestRate
      // math implementation of (1+r)
      double r1 = (1 + r);
      // math implementation of (1+r)^n
      double r2 = Math.pow(r1, n);
      // math implementation of r((1+r)^n)
      double r3 = r * r2;
      // math implementation of ((1+r)^n) - 1
      double r4 = r2 - 1;
      // now r3/r4
      double r5 = r3 / r4;
      // Mortgage calculation
      double mortgage = principal * r5;
      mortgage = Math.round(mortgage * 100.00) / 100.00;
      System.out.println("Your mortgage is: $ " + mortgage);*/
      String message = greetUser("King", "Kong");
      System.out.println(message);
   }
   public static String greetUser (String firstName, String lastName) {
      return "Hello " + firstName +" "+ lastName;

   }

}













