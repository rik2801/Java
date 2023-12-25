import java.text.NumberFormat;
import java.util.Scanner;

public class MortgageCalculator{
    final static byte monthsInAYear = 12;
    final static byte percent = 100;

    public static void main (String args[])
    {

        float principal= (float)readNumber("Principal: $ ", 1000, 1000000);
        float annualInterestRate = (float)readNumber("Annual Interest Rate (%):  ", 0.1, 30);
        float periodYears = (float)readNumber("Years: ", 1, 30);
        //double mortgage = calculateMortgage(principal, annualInterestRate, periodYears);
        //String mortgageFormatted = NumberFormat.getCurrencyInstance(mortgage);
        System.out.println();
        System.out.println("MORTGAGE");
        System.out.println("________");
        System.out.println("Your mortgage is: $ " + calculateMortgage(principal, annualInterestRate, periodYears));
        System.out.println();
        System.out.println("PAYMENT SCHEDULE");
        System.out.println("________________");
        for (short month = 1; month <= periodYears * monthsInAYear; month++){
            double balance = calculateBalance(principal, annualInterestRate, periodYears, month); // why month????
            System.out.println("$ " + balance);
        }
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
            float periodYears) //ask M why redundant?
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
