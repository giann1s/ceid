package LogicGates;

import BinarySignal.BinarySignal;

public class OrGate extends LogicGate {

    public OrGate() {
        super(2);
    }

    public OrGate(Integer inputsNum) {
        super(inputsNum);
    }

    public OrGate(Integer inputsNum, boolean defaultInputsValue) {
        super(inputsNum, defaultInputsValue);
    }

    public OrGate(BinarySignal... inputs) {
        super(inputs);
    }

    public void calcOutput() {
        var value = false;
        var i = 0;

        while (i < inputsNum && ! value) {
            value = inputs.get(i++).getValue();
        }

        setOutput(value);
    }
}
