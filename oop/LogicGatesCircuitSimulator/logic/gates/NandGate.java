package logic.gates;

import java.util.ArrayList;

import binarysignal.BinaryOutputSignal;

public class NandGate extends LogicGate {

    public NandGate() {
        super(2);
    }

    public NandGate(Integer inputsNum) {
        super(inputsNum);
    }

    public NandGate(Integer inputsNum, boolean defaultInputsValue) {
        super(inputsNum, defaultInputsValue);
    }

    public NandGate(ArrayList<BinaryOutputSignal> inputs) {
        super(inputs);
    }

    public NandGate(BinaryOutputSignal... inputs) {
        super(inputs);
    }

    public void calcOutput() {
        var value = true;
        var i = 0;

        while (i < inputsNum && value) {
            value = ! inputs.get(i++).getSignal();
        }

        setOutput(value);
    }
}
