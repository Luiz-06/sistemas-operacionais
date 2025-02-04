class BankersAlgorithm {
    numProcesses: number;
    numResources: number;
    maxMatrix: number[][];
    allocationMatrix: number[][];
    availableResources: number[];
    needMatrix: number[][];

    constructor(numProcesses: number, numResources: number, maxMatrix: number[][], allocationMatrix: number[][], availableResources: number[]) {
        this.numProcesses = numProcesses;
        this.numResources = numResources;
        this.maxMatrix = maxMatrix;
        this.allocationMatrix = allocationMatrix;
        this.availableResources = availableResources;

        this.needMatrix = this.maxMatrix.map((maxRow, i) =>
            maxRow.map((maxVal, j) => maxVal - this.allocationMatrix[i][j])
        );
    }
    
    isSafeState(): [boolean, number[]] {
        const work = [...this.availableResources];
        const finish = Array(this.numProcesses).fill(false);
        const safeSequence: number[] = [];
    
        for (let i = 0; i < this.numProcesses; i++) {
            let found = false;
    
            for (let p = 0; p < this.numProcesses; p++) {
                let canExecute = true;

                for (let j = 0; j < this.numResources; j++) {
                    if (this.needMatrix[p][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
    
                if (!finish[p] && canExecute) {
                    for (let j = 0; j < this.numResources; j++) {
                        work[j] += this.allocationMatrix[p][j];
                    }
    
                    finish[p] = true;
                    safeSequence.push(p);
                    found = true;
                    break;
                }
            }
    
            if (!found) {
                return [false, []];
            }
        }
    
        return [true, safeSequence];
    }

    requestResources(processId: number, request: number[]): boolean {
        if (request.some((req, j) => req > this.needMatrix[processId][j])) {
            throw new Error("Request exceeds maximum need");
        }

        if (request.some((req, j) => req > this.availableResources[j])) {
            return false;
        }

        for (let j = 0; j < this.numResources; j++) {
            this.availableResources[j] -= request[j];
            this.allocationMatrix[processId][j] += request[j];
            this.needMatrix[processId][j] -= request[j];
        }


        const [isSafe] = this.isSafeState();

        if (!isSafe) {
            for (let j = 0; j < this.numResources; j++) {
                this.availableResources[j] += request[j];
                this.allocationMatrix[processId][j] -= request[j];
                this.needMatrix[processId][j] += request[j];
            }
            return false;
        }

        return true;
    }
}


function main() {
    console.log("Test Case 1: Safe State Scenario");
    const numProcesses = 5;
    const numResources = 3;

    const maxMatrix: number[][] = [
        [7, 5, 3],
        [3, 2, 2],
        [9, 0, 2],
        [2, 2, 2],
        [4, 3, 3]
    ];

    const allocationMatrix: number[][] = [
        [0, 1, 0],
        [2, 0, 0],
        [3, 0, 2],
        [2, 1, 1],
        [0, 0, 2]
    ];

    const availableResources: number[] = [3, 3, 2];

    const banker = new BankersAlgorithm(numProcesses, numResources, maxMatrix, allocationMatrix, availableResources);

    const [isSafe, safeSequence] = banker.isSafeState();
    console.log(`Is Safe State: ${isSafe}`);
    console.log(`Safe Sequence: ${safeSequence}`);

    const testRequest: number[] = [1, 0, 2];
    console.log("\nTesting Resource Request:");
    const requestResult = banker.requestResources(0, testRequest);
    console.log(`Request Granted: ${requestResult}`);

    console.log("\nTest Case 2: Unsafe State Scenario");
    const maxMatrixUnsafe: number[][] = [
        [6, 4, 3],
        [3, 2, 2],
        [9, 0, 2],
        [2, 2, 2],
        [4, 3, 3]
    ];

    const allocationMatrixUnsafe: number[][] = [
        [0, 1, 0],
        [3, 0, 2],
        [3, 0, 2],
        [2, 1, 1],
        [0, 0, 2]
    ];

    const availableResourcesUnsafe: number[] = [1, 1, 0];

    const bankerUnsafe = new BankersAlgorithm(numProcesses, numResources, maxMatrixUnsafe, allocationMatrixUnsafe, availableResourcesUnsafe);

    const [isSafeUnsafe, safeSequenceUnsafe] = bankerUnsafe.isSafeState();
    console.log(`Is Safe State: ${isSafeUnsafe}`);
    console.log(`Safe Sequence: ${safeSequenceUnsafe}`);
}

main();
