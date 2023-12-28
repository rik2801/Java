package Java;
import java.text.NumberFormat;
import java.time.LocalDate;
import java.util.Scanner;

public class MortgageCalculator{
    final static byte monthsInAYear = 12;
    final static byte percent = 100;

    public static void main (String args[])
    {
        float principal= (float)readNumber("Principal: $ ", 1000, 1000000);
        float annualInterestRate = (float)readNumber("Annual Interest Rate (%):  ", 0.1, 30);
        float periodYears = (float)readNumber("Years: ", 1, 30);
        printMortgage(principal, annualInterestRate, periodYears); //created using [refactor >>> extract method] to reduce LOC in main method
        printPaymentSchedule(periodYears, principal, annualInterestRate); //created using [refactor >>> extract method] to reduce LOC in main method
    }

    private static void printPaymentSchedule(float periodYears, float principal, float annualInterestRate) {
        LocalDate currentDate = LocalDate.now();
        System.out.println("\n\u001B[1m\u001B[4mPAYMENT SCHEDULE:\u001B[0m"); //bold - \u001B[1m; Underlined - \u001B[4m
        System.out.println("If Paid on: " + currentDate + "\n");
        System.out.println("\u001B[1mUPCOMING PAYMENT DUE DATES AND BALANCE AMOUNT:\u001B[0m");

        for (short month = 1; month <= periodYears * monthsInAYear; month++){
            double balance = calculateBalance(principal, annualInterestRate, periodYears, month); // why month???? >>> this will eventually attribute to the fourth parameter in calculateBalance()
            //increment date by 30 days
            LocalDate futureDate = currentDate.plusDays(30);
            System.out.println("Due date: " + futureDate + " " + "Balance: " + "$ " + balance );
            currentDate = futureDate;
        }
    }

    private static void printMortgage(float principal, float annualInterestRate, float periodYears) {
        float numberOfPayments = periodYears * monthsInAYear; // numberOfPayments
        System.out.println();
        System.out.println("\u001B[1m\u001B[4mMORTGAGE\u001B[0m");
        System.out.println("Your mortgage is: $ " + calculateMortgage(principal, annualInterestRate, periodYears) ); // today's date integration
        System.out.println("No of Payments: " + (int)numberOfPayments);
    }

    public static double readNumber(String prompt, double min, double max){
        Scanner scanner = new Scanner(System.in);
        double value;
        while(true) {
            System.out.print(prompt);
            value = scanner.nextFloat();
            if(value >= min && value <= max)
                break;
            System.out.println("Enter a number between " + min + " and " + max);}
        return value;
    }

    //mortgage calculator
    public static double calculateMortgage(
            float principal,
            float annualInterestRate,
            float periodYears)
    {
        float numberOfPayments = periodYears * monthsInAYear; // numberOfPayments
        double monthlyInterestRate = annualInterestRate / (monthsInAYear * percent); // monthlyInterestRate

        double mortgage = principal * (monthlyInterestRate * Math.pow(1+ monthlyInterestRate, numberOfPayments) / (Math.pow(1+ monthlyInterestRate , numberOfPayments) - 1));
        mortgage =  Math.round(mortgage * 100.00) / 100.00;
        return mortgage;
    }

    public static double calculateBalance(
            float principal,
            float annualInterestRate,
            float periodYears,
            short numberOfPaymentsMade){

        float numberOfPayments = periodYears * monthsInAYear; // numberOfPayments
        double monthlyInterestRate = annualInterestRate / (monthsInAYear * percent); // monthlyInterestRate

        double balance = principal
                * (Math.pow(1 +  monthlyInterestRate, numberOfPayments) - Math.pow(1+monthlyInterestRate, numberOfPaymentsMade))
                / (Math.pow(1 +  monthlyInterestRate, numberOfPayments) - 1);
        balance =  Math.round(balance * 100.00) / 100.00;
        return balance;
    }
}
