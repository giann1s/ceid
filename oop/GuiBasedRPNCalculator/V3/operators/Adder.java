package operators;

import java.util.Stack;
import java.util.EmptyStackException;

public class Adder extends Operator {
    public Adder(Stack<Double> stack) {
        super(stack);
    }

    @Override
    public void operate() {
        try {
            stack.push(stack.pop() + stack.pop());
        }
        catch (EmptyStackException e) {
            System.out.println("Not enough operands for this operation.");
        }
    }
}
