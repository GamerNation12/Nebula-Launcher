import { useLauncher } from '../contexts/LauncherContext';

export interface CoreMessage {
    status: string;
    action?: string;
    modpack_id?: string;
    message?: string;
}

export function useLuminaCore() {
    const { isCoreConnected, lastCoreMessage, startCore, sendCoreCommand } = useLauncher();

    return {
        isConnected: isCoreConnected,
        lastMessage: lastCoreMessage as CoreMessage | null,
        startCore,
        sendCommand: sendCoreCommand
    };
}
