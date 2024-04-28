package LogicGates;

import BinarySignal.BinarySignal;

public class XNOrGate extends LogicGate {

    public XNOrGate() {
        super(2);
    }

    public XNOrGate(Integer inputsNum) {
        super(inputsNum);
    }

    public XNOrGate(Integer inputsNum, boolean defaultInputsValue) {
        super(inputsNum, defaultInputsValue);
    }

    public XNOrGate(BinarySignal... inputs) {
        super(inputs);
    }

    public void calcOutput() {
        var value = true;

        for (BinarySignal input: inputs) {
            if (input.getValue()) {
                value = ! value;
            }
        }

        setOutput(value);
    }
}
